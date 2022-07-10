# Event Handling

- HTML DOM에 클릭하면 이벤트가 발생하고, 발생하면 그에 맞는 변경이 일어나도록 해야한다.
- JSX에 이벤트를 설정할 수 있다.

```js
class Comp extends React.Component {
  render() {
    return (
      <div>
        <button onClick={() => {
          console.log('clicked');
        }}> 클릭 </button>
      </div>
    )
  }
}
```

- ## camelCase로만 사용할 수 있다.
  - onClick, onMouseEnter
- ## 이벤트에 연결된 자바스크립트 코드는 함수다.
  - 이벤트={함수}와 같이 쓴다.
- ## 실제 DOM 요소들에만 사용 가능하다.
  - 리액트 컴포넌트에 사용하면, 그냥 props로 전달한다.

```js
function Component() {
  return (
    <div>
      <button onClick={() => {
        console.log("clicked");
      }}> 클릭 
      </button>
    </div>
  )
}

ReactDOM.render(<Component />, document.querySelector("#root"));
```

```js
class Component extends React.Component {
  state = {
    count: 0,
  };
  
  // constructor(props) {
  //   super(props);
  //   this.click = this.click.bind(this);
  // }

  render() {
    return (
      <div>
        <p>{this.state.count}</p>
        <button onClick={this.click}>
          클릭
        </button>
      </div>
    )
  }

  click() => {
    console.log("clicked");
    this.setState((state) => ({ ...state, count: state.count +1,}));
  }

}
```