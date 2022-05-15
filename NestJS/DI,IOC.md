# DI와 IOC

### 좋은 SW 개발자가 되기 위해서는 좋은 SW 아키텍처를 설계하고 이해하는 공부도 게을리 하지 말아야 한다. 토이 프로젝트의 수준이 아닌 현업에서 작성하는 소프트웨어는 시간이 지날수록 점점 크기가 커지고 복잡해진다. 아키텍처를 가다듬는 작업을 꾸준히 해야 하는 이유이다.

### 객체지향 원칙과 SOLID 설계 원칙, 레이어드 아키텍처 등을 학습할 수 있는 좋은 자료로 `클린 아키텍처`(로버트 C. 마틴 저) 책을 강력히 추천한다. 모든 아키텍처를 다 다루지는 않지만, 종속성을 가지는 컴포넌트들을 버그가 없고 클린하게 설계하는 패턴을 이해하기 쉽게 설명해준다.

---

SOLID원칙의 D에 해당하는 의존성 역전 원칙(Dependency Inversion Principle)을 구현하기 위해서는 IoC(Inversion of Control, 제어역전) 컨테이너라는 기술이 필요하다.  

이미 우리가 앞에서 프로바이더를 다른 컴포넌트에 주입할 때 사용했던 기술이다.  

Nest는 프레임워크에 IoC를 구현하고 있다. 다른 라이브러리를 가져가 붙일 필요없이 사용하기만 하면 되고 그 사용법도 매우 간단하다. 앞에서 봤던 코드를 다시 한번 살펴보자.

```typescript
export class UsersController {
  constructor(private readonly usersService: UsersService) { }
    ...
}
```

UsersControllers는 UsersService에 의존하고 있다. 하지만 UsersService 객체의 라이프 사이클에는 전혀 관여하지 않는다. 어디선가 자신의 생성자에 주어지는 객체를 가져다 쓰고 있을 뿐이다.  

이 역할을 하는 것이 IoC이다. IoC의 도움으로 객체의 라이프 사이클 (물론 최근 객체지향 언어에서는 객체를 메모리에서 삭제하는 일은 가비지 컬렉터가 알아서 해 줍니다)에 신경쓰지 않아도 된다. 이로 인해 코드가 간결해지고 이해하기 쉬워지게 되는 것도 큰 장점이다.

DI (Dependency Injection, 의존성 주입)는 이렇게 IoC 컨테이너가 직접 객체의 생명주기를 관리하는 방식이다.  

예를 들어 A 객체에서 B 객체가 필요하다고 할 때 (A는 B에 의존), A 클래스에는 B 클래스를 직접 생성(new)하여 사용할 수 있다. 여기에서의 문제는 B의 구현체가 변경되었을 때 발생한다. A는 B를 직접 참조하고 있으므로 B가 변경될 때 마다 컴파일러는 A를 다시 컴파일해야 한다. A와 B가 클래스가 아니라 모듈이라고 하면 그 변경의 크기는 더 커지게 되고 컴파일 시간은 더 오래 걸릴 것이다.  

이를 해결하려면 B에 대한 인터페이스 IB를 정의하고, A에서는 IB 타입을 이용하면 된다.
하지만 IB의 구현체 B, B` 등을 직접 생성해야 하는 것은 여전하다. 여기서 IoC의 강력함이 발휘된다.  

예를 들어 IoC를 사용하지 않는 다음과 같은 코드를 보도록 하자.

```typescript
export interface Person {
  getName: () => string;
}

@Injectable()
export class Dexter implements Person {
  getName() {
    return 'Dexter';
  }
}

@Injectable()
export class Jane implements Person {
  getName() {
    return 'Jane';
  }
}

class MyApp {
    private person: Person;
    constructor() {
        this.person = new Dexter();
    }
}
```

L1~17: Person 인터페이스를 구현하는 2개의 클래스 Dexter, Jane이 있습니다. 각 클래스는 getName 함수의 구현체가 다릅니다.

L19~24: MyApp 클래스는 Person타입의 멤버 변수를 가지고 생성자에서 구현체를 생성합니다.

> IoC를 이용하면 이렇게 코드가 바뀐다.

```typescript
class MyApp {
    constructor(@Inject('Person') private p: Person) { }
}
```

이제 Person 객체의 관리는 IoC가 담당하게 된다. Person은 인터페이스인데 Person을 실제 구현한 클래스를 어디선가 정의를 해 두어야 객체를 생성할 수 있을것이다.  

이것은 모듈에서 선언한다.

```typescript
@Module({
  controllers: [UsersController],
  providers: [
    UsersService,
    {
      provide: 'Person',
      useClass: Dexter
    }
  ]
})
...
```

객체로 선언할 때 provide 속성에 토큰을 'Person'으로 주고 있다. 이 토큰은 프로바이더를 가져다 쓸 때 @Inject 데코레이터의 인자로 넘겨준 것과 같다. 만약 Dexter 객체가 아니라 Jane으로 구현을 바꾸고자 한다면 useClass 속성의 클래스 이름만 바꾸면 되는 것이다.

```typescript
@Module({
  controllers: [UsersController],
  providers: [
    UsersService,
    {
      provide: 'Person',
      useClass: Jane
    }
  ]
})
```
