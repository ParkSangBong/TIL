# Decorator

### Nest는 데코레이터를 적극 활용한다. 타입스크립트의 데코레이터는 파이썬의 데코레이터나 자바의 어노테이션과 유사한 기능을 한다. `클래스, 메서드, 접근자, 프로퍼티, 매개변수` 에 적용 가능하다. 각 요소의 선언부 앞에 `@` 로 시작하는 데코레이터를 선언하면 데코레이터로 구현된 코드를 함께 실행한다. 다음 코드는 유저 생성 요청의 본문을 DTO로 표현한 클래스이다.

```typescript
class CreateUserDto {
  @IsEmail()
  @MaxLength(60)
  readonly email: string;

  @IsString()
  @Matches(/^[A-Za-z\d!@#$%^&*()]{8,30}$/)
  readonly password: string;
}
```

> 데코레이터를 이용하여 제대로 요청을 보냈는지 검사를 한다. `email`은 이메일 형식을 가진 문자열인지 판단(`@IsEmail`) 그 길이는 최대 60자 인지 판단(`@MaxLength(60)`), `password`는 문자열인지(`@IsString()`) 해당 정규표현식에 맞는지 판단한다.(`@Matches(...)`)

### 위와 같이 타입스크립트에서 데코레이터를 사용하려면 tsconfig.json파일을 보고 수정해주어야 한다.

tsconfig.json
```json
{
  "compilerOptions": {
        ...
    "experimentalDecorators": true,
        ...
  }
}
```

- experimentalDecorators 옵션이 true로 설정되어 있다. 이 옵션을 켜야 데코레이터를 사용할 수 있다.

### - 데코레이터는 위에서 봤던 것처럼 `@expression`과 같은 형식으로 사용한다. expression은 데코레이팅 된 선언(데코레이터가 선언되는 클래스, 메서드 등)에 대한 정보와 함께 런타임에 호출되는 `함수`여야 한다.

- ### 다음과 같은 메서드 데코레이터가 있고 이 데코레이터를 test라는 메서드에 선언했다. 여기서 deco 함수에 인자들이 있는데 메서드 데코레이터로 사용하기 위해서는 이렇게 정의해야 한다. 
- (이후에 자세히 설명한다고 한다.)

```typescript
function deco(target: any, propertyKey: string, descriptor: PropertyDescriptor) {
  console.log('데코레이터가 평가됨');
}

class TestClass {
  @deco
  test() {
    console.log('함수 호출됨')
  }
}

const t = new TestClass();
t.test();
```

이제 TestClass를 생성하고 test 메서드를 호출하면 다음과 같은 결과가 콘솔에 출력된다.

```console
데코레이터가 평가됨
함수 호출됨
```

만약 데코레이터에 인자를 넘겨서 데코레이터의 동작을 변경하고 싶다? 그럴 땐 데코레이터 팩토리, 즉 데코레이터를 리턴하는 함수를 만들면 된다. 코드를 다음과 같이 바꿔보자

```typescript
function deco(value: string) {
  console.log('데코레이터가 평가됨');
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    console.log(value);
  }
}

class TestClass {
  @deco('HELLO')
  test() {
    console.log('함수 호출됨')
  }
}
```

실행해보면 결과는 다음과 같이 나온다.

```console
데코레이터가 평가됨
HELLO
함수 호출됨
````



# 데코레이터 합성

### 만약 여러개의 데코레이터를 사용한다면 수학에서의 함수 합성과 같이 적용 된다. 다음 데코레이터 선언의 합성 결과는 f(g(x))와 같다.

```typescript
@f
@g
test
```
-> 솔직히 이 부분 아직 이해 안된다.

> 여러 데코레이터를 사용할 때 다음과 같은 단계가 수행 된다.

> 1. 각 데코레이터의 표현은 위에서 아래로 `평가(evaluate)` 됩니다.
> 2. 그런 다음 결과는 아래에서 위로 함수로 `호출(call)` 됩니다.

### 다음은 합성순서에 대한 이해를 도울 수 있는 예이다.

```typescript
function first() {
  console.log("first(): factory evaluated");
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    console.log("first(): called");
  };
}

function second() {
  console.log("second(): factory evaluated");
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    console.log("second(): called");
  };
}

class ExampleClass {
  @first()
  @second()
  method() {
    console.log('method is called');
  }
}
```

```console
first(): factory evaluated
second(): factory evaluated
second(): called
first(): called
method is called
```

# 타입스크립트가 지원하는 5가지 데코레이터를 알아보자

## 1. 클래스 데코레이터 (Class Decorator)

> ### 이름 그대로 클레스 데코레이터는 클래스 바로 앞에 선언된다. 클레스 데코레이터는 클래스의 생성자에 적용되어 클래스 정의를 읽거나 수정할 수 있다. 선언 파일과 선언 클래스 내에서는 사용할 수 없다.

- 클래스에 reportingURL 속성을 추가하는 데코레이터의 예이다.

```typescript
function reportableClassDecorator<T extends { new (...args: any[]): {} }>(constructor: T) { //  L1: 클래스 데코레이터 팩토리입니다. 생성자 타입(new (...args: any[]): {}. new 키워드와 함께 어떠한 형식의 인자들도 받을 수 있는 타입)을 상속받는 제네릭 타입 T 를 가지는 생성자(constructor)를 팩토리 메서스의 인자로 전달하고 있습니다.

  return class extends constructor {  //  L2: 클래스 데코레이터는 생성자를 리턴하는 함수여야 합니다.
    reportingURL = "http://www.example.com";  //  L3: 클래스 데코레이터가 적용되는 클래스에 새로운 reportingURL이라는 새로운 속성을 추가합니다.
  };
}

@reportableClassDecorator
class BugReport {
  type = "report";
  title: string;

  constructor(t: string) {
    this.title = t;
  }
}

const bug = new BugReport("Needs dark mode");
console.log(bug);
```

- 위 코드의 출력결과는 다음과 같다.

```typescript
{type: 'report', title: 'Needs dark mode', reportingURL: 'http://www.example.com'}
```

### - 여기서 BugReport 클래스에 선언되지 않은 새로운 속성 reportURL이 추가 된 것을 확인할 수 있다.

### ※ 클래스의 타입이 변경되는 것은 아니다. 타입 시스템은 reportingURL을 인식하지 못하기 때문에 `bug.reportingURL`과 같이 직접 사용할 수는 없다.

## 2. 메서드 데코레이터 (Method Decorator)

> ### 메서드 데코레이터는 메서드 바로 앞에 선언된다. 메서드의 속성 디스크립터에 적용되고 메서드의 정의를 읽거나 수정할 수 있다. 선언 파일과 오버로드 메서드, 선언 클래스에 사용할 수 없다.

> 앞서 deco 메서드 데코레이터에서 보았던 것처럼 메서드 데코레이터는 다음 세 개의 인수를 가진다.

  1. 정적 멤버가 속한 클래스의 생성자 함수이거나 인스턴스 맴버에 대한 클래스의 프로토타입
  2. 맴버의 이름
  3. 맴버의 속성 디스크립터. PropertyDescriptor 타입을 가진다.

  ### ※ PropertyDescriptor interface
  ```typescript
    interface PropertyDescriptor {
    configurable?: boolean;  // 속성의 정의를 수정할 수 있는지 여부
    enumerable?: boolean;    // 열거형인지 여부
    value?: any;             // 속성 값
    writable?: boolean;      // 수정 가능 여부
    get?(): any;             // getter
    set?(v: any): void;      // setter
  }
  ```

  - 만약 메서드 데코레이터가 값을 반환한다면 이는 해당 메서드의 속성 디스크립터가 된다.

- 메서드 데코레이터의 예를 보도록 하자. 함수를 실행하는 과정에서 에러가 발생했을 때 이 에러를 캐치하고 처리하는 로직을 구현하고 있다.

```typescript
function HandleError() {
  return function(target: any, propertyKey: string, descriptor: PropertyDescriptor) { //  L2: 메서드 데코레이터가 가져야 하는 3개의 인자입니다. PropertyDescriptor는 객체 속성의 특성을 기술하고 있는 객체로써 enumerable 외에도 여러가지 속성을 가지고 있습니다. enumerable이 true가 되면 이 속성은 열거형이라는 뜻이 됩니다.
    console.log(target) //  L3: 출력결과는 {constructor: ƒ, greet: ƒ} 입니다. 데코레이터가 선언된 메서드 hello가 속해있는 클래스의 생성자와 프로토타입을 가지는 객체임을 알 수 있습니다.
    console.log(propertyKey)  //  L4: 함수이름 hello가 출력됩니다.
    console.log(descriptor) //  L5: hello 함수가 처음 가지고 있던 디스크립터가 출력됩니다. 출력결과는 {value: ƒ, writable: true, enumerable: false, configurable: true} 입니다.



    const method = descriptor.value;  //  L7: 디스크립터의 value 속성으로 원래 정의된 메서드를 저장합니다.

    descriptor.value = function() {
      try {
        method(); //  L10: 원래의 메서드를 호출합니다.
      } catch (e) {
        // 에러 핸들링 로직 구현, L12: 만약 원래의 메서드를 수행하는 과정에서 발생한 에러를 핸들링하는 로직을 이 곳에 구현합니다.
        console.log(e); //  L13: Error: 테스트 에러가 출력됩니다.
      }
    }
  };
}

class Greeter {
  @HandleError()
  hello() {
    throw new Error('테스트 에러');
  }
}

const t = new Greeter();
t.hello();
```

## 3. 접근자 데코레이터 (Accessor Decorator)

> ### 접근자 데코레이터는 접근자 바로 앞에 선언한다. 접근자의 속성 디스크립터에 적용되고 접근자의 정의를 읽거나 수정할 수 있다. 역시 선언 파일과 선언 클래스에 사용할 수 없다. 접근자 데코레이터가 반환하는 값은 해당 맴버의 속성 디스크립터가 된다.

- 특정 맴버를 열거가 가능한 지 결정하는 데코레이터의 예를 살펴 보자.

```typescript
function Enumerable(enumerable: boolean) {
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    descriptor.enumerable = enumerable; //  L3: 디스크립터의 enumerable 속성을 데코레이터의 인자로 결정합니다.
  }
}

class Person {
  constructor(private name: string) {}  //  L8: name은 외부에서 접근하지 못하는 private 멤버입니다.

  @Enumerable(true)
  get getName() { //  L10~13: 게터 getName 함수는 열거가 가능하도록 합니다.

    return this.name;
  }

  @Enumerable(false)
  set setName(name: string) { //  L15~16: 세터 setName 함수는 열거가 불가능하도록 합니다.
    this.name = name;
  }
}

const person = new Person('Dexter');
for (let key in person) { //  L21~24: 결과를 출력하면 getName은 출력되지만 setName은 열거하지 못하게 되었기 때문에 for문에서 key로 받을 수가 없습니다.
  console.log(`${key}: ${person[key]}`);
}
```

```
name: Dexter
getName: Dexter
```

## 4. 속성 데코레이터 (Property Decorators)

> ### 속성 데코레이터는 클래스의 속성 바로 앞에 선언된다. 역시 선언 파일, 선언 클래스에서 사용하지 못한다. 속성 데코레이터는 다음 두 개의 인수를 가지는 함수이다.

  1. 정적 멤버가 속한 클래스의 생성자 함수이거나 인스턴스 맴버에 대한 클래스의 프로토타입
  2. 맴버의 이름

- ### 메서드 데코레이터나 접근자 데코레이터와 비교했을 때 세 번째 인자인 속성 디스크립터가 존재하지 않는다. 공식문서에 따르면 반환값도 무시되고, 이는 현재 프로토타입(prototype)의 맴버를 정의할 때 인스턴스 속성을 설명하는 메커니즘이 없고 속성의 초기화 과정을 관찰하거나 수정할 수 있는 방법이 없기 때문이라고 한다.

```typescript
function format(formatString: string) {
  return function (target: any, propertyKey: string): any {
    let value = target[propertyKey];

    function getter() {
      return `${formatString} ${value}`;
    } //  L6: 게터에서 데코레이터 인자로 들어온 formatString을 원래의 속성과 조합한 스트링으로 바꿉니다.

    function setter(newVal: string) {
      value = newVal;
    }

    return {
      get: getter,
      set: setter,
      enumerable: true,
      configurable: true,
    }
  }
}

class Greeter {
  @format('Hello')  //  L23: 데코레이터에 formatString을 전달합니다.
  greeting: string;
}

const t = new Greeter();
t.greeting = 'World';
console.log(t.greeting);  //  L29: 속성을 읽을 때 게터가 호출되면서 Hello World가 출력됩니다.
```

## 5. 매개변수 데코레이터 (Parameter Decorator)

> ### 생성자 또는 메서드의 파라미터에 선언되어 적용된다. 선언 파일, 선언 클래스에서 사용할 수 없다. 매개변수 데코레이터는 호출 될 때 3가지의 인자와 함께 호출 된다. 반환값은 무시한다.

  1. 정적 맴버가 속한 클래스의 생성자 함수이거나 인스턴스 맴버에 대한 클래스의 프로토타입
  2. 맴버의 이름
  3. 매개변수가 함수에서 몇 번째 위치에 선언되었는 지를 나타내는 인덱스

- 파라미터 유효성 검사를 하는 데코레이터를 만들어 보겠다. 매개변수 데코레이터는 단독으로 사용하는 것보다 함수 데코레이터와 함께 사용할 때 유용하게 쓰인다.

### ※ Nest에서 API 요청 파라미터에 대해 유효성 검사를 할 때 이와 유사한 데코레이터를 많이 사용한다. 참고하도록 하자!

```typescript
import { BadRequestException } from '@nestjs/common';

function MinLength(min: number) { //  L3: 파라미터의 최소값을 검사하는 파라미터 데코레이터
  return function (target: any, propertyKey: string, parameterIndex: number) {
    target.validators = { //  L5~9: target 클래스(여기서는 User)의 validators 속성에 유효성을 검사하는 함수를 할당합니다.
      minLength: function (args: string[]) {  //  L6: args 인자는 18번 라인에서 넘겨받은 메서드의 인자입니다.
        return args[parameterIndex].length >= min;  //  L7: 유효성 검사를 위한 로직입니다. parameterIndex에 위치한 인자의 길이가 최소값보다 같거나 큰지 검사합니다.
      }
    }
  }
}

function Validate(target: any, propertyKey: string, descriptor: PropertyDescriptor) { //  L13: 함께 사용할 메서드 데코레이터
  const method = descriptor.value;  //  L14: 메서드 데코레이터가 선언된 메서드를 method 변수에 임시 저장해 둡니다.

  descriptor.value = function(...args) {  //  L16: 디스크립터의 value에 유효성 검사 로직이 추가된 함수를 할당합니다.


    Object.keys(target.validators).forEach(key => { //  L17~21: target(User 클래스)에 저장해 둔 validators를 모두 수행합니다. 이때 원래 메서드에 전달된 인자(args)들을 각 validator에 전달합니다.
      if (!target.validators[key](args)) {
        throw new BadRequestException();
      }
    })
    method.apply(this, args); //  L22: 원래의 함수를 실행합니다.
  }
}

class User {
  private name: string;

  @Validate
  setName(@MinLength(3) name: string) {
    this.name = name;
  }
}

const t = new User();
t.setName('Dexter');  //  L36: 파라미터 name의 길이가 5이기 때문에 문제가 없습니다.
console.log('----------')
t.setName('De');  //  L38: 파라미터 name의 길이가 3보다 작기 때문에 BadRequestException이 발생합니다.
```

# 지금까지 5가지 데코레이터를 자세히 알아보았다. 각 데코레이터의 특징을 간략히 정리하면 다음과 같다.

| 데코레이터 | 역할 | 호출시 전달되는 인자 | 선언 불가능한 위치 |
| --- | --- | --- | --- |
| 클래스 데코레이터 | 클래스의 정의를 읽거나 수정 | (constructor) | d.ts 파일, declare 클래스 |
| 메서드 데코레이터 | 메서드의 정의를 읽거나 수정 | (target, propertyKey, propertyDescriptor) | d.ts 파일, declare 클래스, 오버로드 메서드 |
| 접근자 데코레이터 | 접근자의 정의를 읽거나 수정 | (target, propertyKey, propertyDescriptor) | d.ts 파일, declare 클래스 |
| 속성 데코레이터 | 속성의 정의를 읽음 | (target, propertyKey) | d.ts 파일, declare 클래스 |
| 매개변수 데코레이터 | 매개변수의 정의를 읽음 | (target, propertyKey, parameterIndex) | d.ts 파일, declare 클래스 |