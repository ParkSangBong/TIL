- ## Props 는 컴포넌트 외부에서 컴포넌트에게 주는 데이터이다.
- ## State 는 컴포넌트 내부에서 변경할 수 있는 데이터이다.
- ## 둘 다 변경이 발생하면, 렌더링이 다시 일어날 수 있다.

## Render 함수
- ## Props와 State 를 바탕으로 컴포넌트를 그린다.
- ## 그리고 Props와 State 가 변경되면, 컴포넌트를 다시 그린다.
- ## 컴포넌트를 그리는 방법을 기술하는 함수가 랜더 함수이다.

# Props

```js
//  {message: '안녕하세요!!!'}
function Component(props) {
  return (
    <div>
      <h1> {props.message} 이것은 함수로 만든 컴포넌트 입니다. </h1>
    </div>
  )
}

Component.defaultProps = {
  message: "기본값!!!!!",
}

ReactDOM.render(
  <Component message="기본값 아님!!!" />,
  document.querySelector("#root")
);
```

```js
class Component extends React.Component {
  render() {
    return (
      <div>
        <h1>{this.props.message} 이것은 클래스로 만든 컴포넌트 입니다. </h1>
      </div>
    )
  }

  static defaultProps = {
    message: "기본값2",
  }

}

// Component.defaultProps = {
//   message: "기본값",
// }

ReactDOM.render(
  <Component />,
  document.querySelector("#root")
);
```

# State

```js
class Component extends React.Component {
  // 클래스 컴포넌트에서 state는 항상 객체여야 한다.
  // state = {
  //   count: 0,
  // }

  constructor(props) {
    super(props);

    //  state 초기화
    this.state = {
      count: 0
    };
  }

  render() {
    return (
      <div>
        <h1>{this.props.message} 이것은 클래스로 만든 컴포넌트 입니다. </h1>
        <p> {this.state.count} </p>
      </div>
    )
  }

  componentDidMount() {
    setTimeOut(() => {
      // this.state.count = this.state.count + 1;
      // this.setState({
      //   count: this.state.count + 1,
      // })
      this.setState(() => {
        const newState = {
          count: previousState.count + 1
        };
        return newState;
      })
    }, 1000);
  }

  static defaultProps = {
    message: "기본값2",
  }

}

// Component.defaultProps = {
//   message: "기본값",
// }

ReactDOM.render(
  <Component message="기본값 아님" />,
  document.querySelector("#root")
);
```