# React.createElement

```js
React.createElement(
  type, // 태그 이름 문자열 | 리액트 컴포넌트 | React.Fragment
  [props],  //  리액트 컴포넌트에 넣어주는 데이터 객체
  [ ... children] //  자식으로 넣어주는 요소들
)
```

## 1. 태그 이름 문자열 type
```js
ReactDOM.render(
  React.createElement('h1', null, `type 이 "태그 이름 문자열" 입니다.`)
  document.querySelector("#root")
);
```

## 2. 리액트 컴포넌트 type
```js
const Componet = () => {
  return React.createElement(
    'p', 
    null, 
    `type 이 "React 컴포넌트" 입니다.`)
}
ReactDom.render(
  // <Component></Component> => <Component /> => <p>type이 "React 컴포넌트" 입니다."</p>
  React.createElement(Component, null, null),
  document.querySelector("#root")
);
```

## 3. React.Fragment
```js
ReactDOM.render(
  React.createElement(
    React.Fragment,
    null,
    `type이 "React Fragment" 입니다.`,
    `type이 "React Fragment" 입니다.`,
    `type이 "React Fragment" 입니다.`
  ),
  document.querySelector("#root")
)
```

## 4. 복잡한 리액트 엘리먼트 모임
```js
ReactDOM.render(
  React.createElement('div', null, 
    React.createElement('div', null, 
      React.createElement('h1', null, "주제"), 
      React.createElement('ul', null, 
        React.createElement('li', null, "React"),
        React.createElement('li', null, "Vue"),
      )
    )
  ),
  document.querySelector("#root")
)
```