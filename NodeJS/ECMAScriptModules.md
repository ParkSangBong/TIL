# ESM

#### ECMAScript modules은 Javascript 코드를 패키징하는 공식 표준 형식이다.
#### module은 import 및 export 문을 사용하여 정의된다.

```mjs
// addTwo.mjs
function addTwo(num) {
  return num + 2;
}

export { addTwo };
```

```mjs
// app.mjs
import { addTwo } from './addTwo.mjs';

// Prints: 6
console.log(addTwo(4));
```

- #### Node.js는 ECMAScript modules을 완벽히 지원하며 원래 모듈 형식인 CommonJS 와 상호 운용성을 제공한다.
- #### Node.js 사용자는 .mjs 파일 확장자, package.json의 "type" 필드 혹은 --input-type 플래그를 사용하여 ECMAScript 모듈 로더를 사용한다.
- #### 이외의 경우엔 CommonJS 모듈 로더를 사용할 것이다.

<br/>

## ES modules 와 CommonJS의 차이점

- ### No require, exports, module.exports
  - 대부분의 경우 ES module은 import를 사용하여 CommonJS modules을 사용할 수 있다.

- ### No __filename or __dirname
  - ES modules에선 위와 같은 CommonJS 변수를 사용할 수 없다.

- ### No Addon Loading

- ### No require.resolve

- ### No NODE_PATH#

- ### No require.extensions#
  - import하기 위해 require.extensions를 사용하지 않는다.
  - 미래엔 이 역할을 loader hooks가 제공할 예정이다.

- ### No require.cache#
  - ECMAScript 모듈 로더에는 별도의 캐시가 존재하기 때문에 캐시를 import해서 사용하지 않는다.
