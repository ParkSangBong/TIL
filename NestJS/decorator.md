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