# 스코프 (Scope)

### Node.js는 다른 웹 프레임워크와는 다르게 멀티 쓰레드 상태 비저장(Multi-Threaded Stateless) 모델을 따르지 않는다. 따라서 싱글톤 인스턴스를 사용하는 것은 안전한 방식이다. 이는 요청으로 들어오는 모든 정보(DB 커넥션 풀, 전역 싱글턴 서비스 등)들을 공유할 수 있다는 것을 의미한다.

### 하지만 GraphQL 애플리케이션의 요청별 캐싱을 한다거나 요청을 추적하거나 또는 멀티테넌시를 지원하기 위해서는 요청 기반으로 생명 주기를 제한해야 한다.  

---

### ※ 멀티 테넌시란?
> ### 하나의 애플리케이션 인스턴스가 여러 사용자에게 각각 다르게 동작하도록 하는 SW 아키텍처를 말한다. 반대로 각 사용자마다 인스턴스가 새로 만들어 지도록 하는 멀티 인스턴스 방식이 있다. 요즘 대부분의 서비스는 멀티 테넌시 방식을 채택하고 있다.

---

### 컨트롤러와 프로바이더에 생명 주기를 스코프 옵션을 주어 지정할 수 있는 방법이 있다.

### 먼저 각각에 지정하는 방법을 알아보기 전에 스코프에는 어떤 것들이 있는지 살펴보자. 

  - `DEFAULT` : 싱글톤 인스턴스가 전체 애플리케이션에서 공유된다. 인스턴스 수명은 애플리케이션 수명주기와 같으며 애플리케이션이 부트스트랩(애플리케이션 또는 시스템이 구동되는 것) 과정을 마치면 모든 싱글톤 프로바이더의 인스턴스가 만들어진다. 따로 선언하지 않으면 `DEFAULT`가 적용된다.

  - `REQUEST` : 들어오는 요청마다 별도의 인스턴스가 생성된다. 요청을 처리하고 나면 인스턴스는 쓰레기 수집(garbage-collected)된다.

  - `TRANSIENT` : 이 스코프를 지정한 인스턴스는 공유되지 않는다. 임시(TRANSIENT) 프로바이더를 주입하는 각 컴포넌트는 새로 생성된 전용 인스턴스를 주입받게 된다.

    ※ 가능하면 DEFAULT 스코프를 사용하는 것을 권장하는데 싱글톤 인스턴스를 공유한다는 것은 인스턴스를 캐시할 수 있고, 초기화가 애플리케이션 시작중에 한번만 발생하기 때문에 메모리와 동작 성능을 향상시킬수 있기 때문이다.

## 프로바이더에 스코프 적용하기

---

### @Injectable() 데코레이터에 scope 속성을 주는 방법.

```typescript
import { Injectable, Scope } from '@nestjs/common';

@Injectable({ scope: Scope.REQUEST })
export class CatsService {}
```

커스텀 프로바이더를 사용할 때 역시 마찬가지다.

```typescript
{
  provide: 'CACHE_MANAGER',
  useClass: CacheManager,
  scope: Scope.TRANSIENT,
}
```

## 컨트롤러에 스코프 적용하기 

---

### @Controller() 데코레이터는 ControllerOptions을 인자로 받을 수 있다. ControllerOptions는 ScopeOptions를 상속한다.

```typescript
export declare function Controller(options: ControllerOptions): ClassDecorator;

export interface ControllerOptions extends ScopeOptions, VersionOptions {
    path?: string | string[];
    host?: string | RegExp | Array<string | RegExp>;
}

export interface ScopeOptions {
    scope?: Scope;
}
```

따라서 다음 코드와 같이 scope 속성을 전달할 수 있다.

```typescript
@Controller({
  path: 'cats',
  scope: Scope.REQUEST,
})
export class CatsController {}
```

## 스코프 계층(Scope hierarchy)

---

### 스코프는 컨트롤러와 프로바이더에 선언할 수 있는데 만약 연관된 컴포넌트들이 서로 다른 스코프를 가지게 된다면 어떻게 될까?

### 예를 들어 CatsController -> CatsService -> CatsRepository와 같은 종속성 그래프를 가지고 있는 상태에서 CatsService는 REQUEST 스코프를 가지고, 나머지는 모두 DEFAULT 스코프를 가질 경우를 가정해 보자.

### 이때 CatsController는 CatsService에 의존적이기 때문에 REQUEST로 변경된다. 하지만 CatsRepository는 CatsService에 의존하고 있지 않으므로 그대로 DEFAULT로 남게 된다. 

### 결과적으로 종속성을 가진 컴포넌트의 스코프를 따라가게 된다.