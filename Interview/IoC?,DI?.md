# IoC

- ### 우리가 프레임워크 없이 개발할 때에는 객체의 생성, 설정, 초기화, 메서드 호출, 소멸을 개발자가 직접 관리한다. 전통적인 프로그래밍에서의 흐름은 개발자가 작성한 프로그램이 외부 라이브러리의 코드를 호출해 이용한다. 하지만 프레임워크를 사용하면 객체의 생명 주기를 모두 프레임워크에 위임할 수 있다. 즉 외부 라이브러리가 개발자가 작성한 코드를 호출하고, 흐름을 제어한다.
- ### 이와 같이 `개발자가 작성한 객체나 메서드의 제어를 개발자가 아니라 외부에 위임하는 설계 원칙을 제어의 역전`이라고 한다.
- ### 어플리케이션의 제어 책임이 프로그래머에서 프레임워크로 위임되므로, 개발자는 비즈니스 로직에 더 집중할 수 있다는 장점이 있다.

<br>

# Nest에서의 IoC

- ### Nest는 프레임워크에 IoC를 구현하고 있다. 다른 라이브러리를 가져가 붙일 필요없이 사용하기만 하면 되고 그 사용법도 매우 간단하다.

```ts
export class UsersController {
  constructor(private readonly usersService: UsersService) { }
    ...
}
```

- ### UsersController는 UsersService에 의존하고 있습니다. 하지만 UsersService 객체의 라이프 사이클에는 전혀 관여하지 않는다. 어디선가 자신의 생성자에 주어지는 객체를 가져다 쓰고 있을 뿐이다. 이 역할을 하는 것이 IoC이다.

<br>

# DI (Dependency Injection, 의존성 주입)

- ### IoC 컨테이너가 직접 객체의 생명주기를 관리하는 방식이다.
- ### 객체의 의존성을 개발자가 아닌 외부(IoC 컨테이너)에서 주입하기 한다.
- ### 객체간의 결합을 약하게 해주며 유지 보수가 좋은 코드를 만들어준다.

<br>

# Nest에서의 DI와 IoC

### 다음과 같이 IoC를 사용하지 않는 코드가 있다.

```ts
export interface Person {
  getName: () => string;
}

@Injectable()
export class Jack implements Person {
  getName() {
    return 'Jack';
  }
}

@Injectable()
export class Angela implements Person {
  getName() {
    return 'Angela';
  }
}

class MyApp {
    private person: Person;
    constructor() {
        this.person = new Jack();
    }
}
```

### IoC를 이용하면 다음과 같이 바꿀 수 있다.

```ts
class MyApp {
    constructor(@Inject('Person') private p: Person) { }
}
```

- ### 이제 Person 객체의 관리는 IoC가 담당한다. Person은 인터페이스인데 실제 구현한 클래스를 어디선가 정의를 해 두어야 객체를 생성할 수 있을 것이다. 이것은 모듈에서 선언한다.

```ts
@Module({
  controllers: [UsersController],
  providers: [
    UsersService,
    {
      provide: 'Person',
      useClass: Jack
    }
  ]
})
```

### 객체로 선언할 때 provide 속성에 토큰을 'Person'으로 주고 있다. 이 토큰은 프로바이더를 가져다 쓸 때 @Inject 데코레이터의 인자로 넘겨준 것과 같다.
### 만약 Jack 객체가 아니라 Angela로 구현을 바꾸고자 한다면 useClass 속성의 클래스 이름만 바꾸면 된다.

<br>

# 출처 : [hudi.blog](https://hudi.blog/inversion-of-control/), [NestJS로 배우는 백엔드 프로그래밍](https://wikidocs.net/150160)