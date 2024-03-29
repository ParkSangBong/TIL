# 스코프 (Scope)

### Node.js는 멀티 쓰레드 상태 비저장 모델을 따르지 않는다고 한다. 그렇기 때문에 싱글톤 인스턴스를 사용하는 것은 안전한 방식이라고 한다.
### 이는 요청으로 들어오는 모든 정보(DB 커넥션 풀, 전역 싱글톤 서비스 등)들을 공유할 수 있다는 것을 의미한다.

### 하지만 GraphQL 애플리케이션의 요청별 캐싱을 한다거나 요청을 추적하거나 또는 멀티테넌시를 지원하기 위해서는 요청 기반으로 생명 주기를 제한해야 한다고 한다.

> ## 멀티 테넌시란?  
> 하나의 애플리케이션 인스턴스가 여러 사용자에게 각각 다르게 동작하도록 하는 SW 아키텍처를 말합니다. 반대로 각 사용자마다 인스턴스가 새로 만들어 지도록 하는 멀티 인스턴스 방식이 있습니다. 요즘 대부분의 서비스는 멀티 테넌시 방식을 채택하고 있습니다.

<br>

# 스코프의 종류

- ### DEFAULT : 싱글톤 인스턴스가 전체 애플리케이션에서 공유됩니다. 인스턴스 수명은 애플리케이션 수명주기와 같습니다. 애플리케이션이 부트스트랩(각주. 애플리케이션 또는 시스템이 구동되는 것) 과정을 마치면 모든 싱글톤 프로바이더의 인스턴스가 만들어집니다. 따로 선언하지 않으면 DEFAULT가 적용됩니다.

- ### REQUEST : 들어오는 요청마다 별도의 인스턴스가 생성됩니다. 요청을 처리하고 나면 인스턴스는 쓰레기 수집(garbage-collected)됩니다.

- ### TRANSIENT : 이 스코프를 지정한 인스턴스는 공유되지 않습니다. 임시(TRANSIENT) 프로바이더를 주입하는 각 컴포넌트는 새로 생성된 전용 인스턴스를 주입받게됩니다.

<br>

# 스코프 계층(Scope hierarchy)

### 스코프는 컨트롤러와 프로바이더에 선언할 수 있는데 만약 연관된 컴포넌트들이 서로 다른 스코프를 가지게 된다면 어떻게 될까요? 
### 예를 들어 CatsController → CatsService → CatsRepository 와 같은 종속성 그래프를 가지고 있는 상태에서 CatsService는 REQUEST 스코프를 가지고, 나머지는 모두 DEFAULT 스코프를 가질 경우를 가정해 봅시다. 
### 이때 CatsController는 CatsService에 의존적이기 때문에 REQUEST로 변경됩니다. 하지만 CatsRepository는 CatsService에 의존하고 있지 않으므로 그대로 DEFAULT로 남게 됩니다. 종속성을 가진 컴포넌트의 스코프를 따라가게 됩니다.

# 출처 : [NestJS로 배우는 백엔드 프로그래밍](https://wikidocs.net/150160)