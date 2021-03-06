# 호이스팅(hoisting)

JavaScript에서 **호이스팅**(hoisting)이란, 인터프리터가 변수와 함수의 메모리 공간을 선언 전에 미리 할당하는 것을 의미합니다. `var`로 선언한 변수의 경우 호이스팅 시 `undefined`로 변수를 초기화합니다. 반면 `let`과 `const`로 선언한 변수의 경우 호이스팅 시 변수를 초기화하지 않습니다.

호이스팅을 설명할 땐 주로 "변수의 선언과 초기화를 분리한 후, 선언만 코드의 최상단으로 옮기는" 것으로 말하곤 합니다. 따라서 변수를 정의하는 코드보다 사용하는 코드가 앞서 등장할 수 있습니다. 다만 선언과 초기화를 함께 수행하는 경우, 선언 코드까지 실행해야 변수가 초기화된 상태가 됨을 주의하세요.

즉, 앞서 선언하지 않은 변수가 먼저 선언되어 호출되는 것처럼 동작하는 프로세스를 말한다.예를 들면 다음과 같다.

```
console.log(b) // undefined
var b = "something"

console.log(b) // Error: Uncaught ReferenceError: b is not defined
let b = "something
```

`let`으로 선언한 변수는 선언 전에 호출하게 되면 참조 오류가 발생하는 반면 `var`로 선언한 변수는 `undefined`로 할당값을 초기화한 상태로 출력된다.

변수 생성 과정은 `선언 단계(Declaration phase)` => `초기화 단계(Initialization phase)` => `할당 단계(Assignment phase)` 이렇게 총 세 단계를 거쳐 생성되는데, `var`로 선언된 변수는 선언 단계에서 `undefined`를 할당하는 과정(초기화 과정)이 한 번에 진행되어서 변수 선언 전 호이스팅이 가능하지만, `let`은 선언 단계에서 초기화 과정(메모리 공간 확보)이 이루어지지 않기 때문에 선언 이전에 변수를 참조할 수 없다.