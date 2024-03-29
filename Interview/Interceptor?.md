# Interceptor (인터셉터)

### 인터셉터는 요청과 응답을 가로채서 변형을 가할 수 있는 컴포넌트이다.

- ### 인터셉터는 AOP(관점 지향 프로그래밍)에 영향을 많이 받았습니다.

- ### 각 인터셉터에는 intercept() 메서드를 구현해야하고 이는 2개의 인자를 가진다.
  - ### ExecutionContext와 CallHandler로 이루어져있다.
  - ### CallHandler 인터페이스는 handle() 메서드를 구현해야 한다.

### 인터셉터는 다음과 같은 기능들을 수행할 수 있다.

- 메서드 실행 전/후 추가 로직 바인딩
- 함수에서 반환된 결과를 변환
- 함수에서 던져진 예외를 변환
- 기본 기능의 동작을 확장
- 특정 조건에 따라 기능을 완전히 재정의(예: 캐싱)