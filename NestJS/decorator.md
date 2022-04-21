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