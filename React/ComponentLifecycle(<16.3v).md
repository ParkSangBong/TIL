# Component Lifecycle

- 리액트 컴포넌트는 탄생부터 죽음까지 여러지점에서 개발자가 작업이 가능하도록 메서드를 오버라이딩 할 수 있게 해준다.

- ## Declarative

<img width="1223" alt="스크린샷 2022-07-11 오후 5 05 36" src="https://user-images.githubusercontent.com/25292654/178217567-59cce6d5-2c99-48fb-b6f8-7c19763da7e3.png">

  - shouldComponentUpdate : 불필요하게 렌더되는것을 막는 라이프 사이클 훅

# Component 생성 및 마운트, React 16.3 이전 버전 기준

| |
| --- |
| constructor|
| componentWillMount |
| render (최초 렌더) |
| componentDidMount |

```js
class App extends React.Component {
  
  state = {
    age: 39,
  }

  constructor(props) {
    super(props);

    console.log('constructor', props);
  }

  render() {
    console.log('render');
    return (
      <div>
        <h2>Hello {this.props.name} - {this.state.age} </h2>
      </div>
    )
  }

  componentWillMount() {
    console.log("componentWillMount");
  }

  componentDidMount() {
    console.log("componentDidMount");

    setInterval(() => {
      // console.log("setInterval");
      this.setState(state => ({...state, age: state.age + 1}))
    }, 1000)

  }

}

ReactDOM.render(<App name="Lowerd" />, document.querySelector("#root"))
```

# Component props, state 변경, React 16.3 이전 기준

| |
| --- |
| componentWillReceiveProps |
| shouldComponentUpdate |
| componentWillUpdate |
| render |
| componentDidUpdate |

```js
class App extends React.Component {
  
  state = {
    age: 39,
  }

  constructor(props) {
    super(props);

    console.log('constructor', props);
  }

  render() {
    console.log('render');
    return (
      <div>
        <h2>Hello {this.props.name} - {this.state.age} </h2>
      </div>
    )
  }

  componentWillMount() {
    console.log("componentWillMount");
  }

  componentDidMount() {
    console.log("componentDidMount");

    setInterval(() => {
      // console.log("setInterval");
      this.setState(state => ({...state, age: state.age + 1}))
    }, 1000)

  }

  componentWillReceiveProps(nextProps) {
    console.log("componentWillReceiveProps", nextProps);
  }

  shouldComponentUpdate(nextProps, nextState) {
    console.log("shouldComponentUpdate", nextProps, nextState);
    // return false; // 재렌더링이 되지 않는다
    return true;
  }

  componentWillUpdate(nextProps, nextState) {
    console.log("componetWillUpdate", nextProps, nextState);
  }

  componentDidUpdate(prevProps, prevState) {
    console.log("componentDidUpdate", prevProps, prevState)
  }

}

ReactDOM.render(<App name="Lowerd" />, document.querySelector("#root"))
```

## componentWillReceiveProps
- props를 새로 지정했을 때 바로 호출된다.
- state의 변경에 반응하지 않는다.
  - 만약 props의 값에 따라 state를 변경해야 한다면, setState를 이용해 state를 변경한다. 그러면 다음 이벤트로 각각 가는것이 아니라 한번에 변경된다.

## shouldComponentUpdate
- props만 변경될 때
- state만 변경될 때
- props & state 둘다 변경될 때
- newProps와 newState를 인자로 해서 호출
- return type이 boolean이다.
  - true면 render
  - false면 render가 호출되지 않는다.
  - 이 함수를 구현하지 않으면, 디폴트는 true

## componentWillUpdate
- 컴포넌트가 재 렌더링 되기 직전에 불린다.
- 여기선 setState같은 것을 쓰면 안된다.

## componentDidUpdate
- 컴포넌트가 재 렌더링을 마치면 불린다.

<br>

# Component 언마운트, 리액트 16.3 이전 버전 기준

```js
class App extends React.Component {
  
  state = {
    age: 39,
  }
  
  interval = null;
  
  constructor(props) {
    super(props);

    console.log('constructor', props);
  }

  render() {
    console.log('render');
    return (
      <div>
        <h2>Hello {this.props.name} - {this.state.age} </h2>
      </div>
    )
  }

  componentWillMount() {
    console.log("componentWillMount");
  }

  componentDidMount() {
    console.log("componentDidMount");

    this.interval = setInterval(() => {
      // console.log("setInterval");
      this.setState(state => ({...state, age: state.age + 1}))
    }, 1000)

  }

  componentWillReceiveProps(nextProps) {
    console.log("componentWillReceiveProps", nextProps);
  }

  shouldComponentUpdate(nextProps, nextState) {
    console.log("shouldComponentUpdate", nextProps, nextState);
    // return false; // 재렌더링이 되지 않는다
    return true;
  }

  componentWillUpdate(nextProps, nextState) {
    console.log("componetWillUpdate", nextProps, nextState);
  }

  componentDidUpdate(prevProps, prevState) {
    console.log("componentDidUpdate", prevProps, prevState)
  }

  componentWillUnmount() {
    clearInterval(this.interval);
  }

}

ReactDOM.render(<App name="Lowerd" />, document.querySelector("#root"))
```