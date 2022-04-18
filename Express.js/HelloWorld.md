# Installing

1. 디렉토리를 만드세요
   > <code> $ mkdir yourapp </code>

   > <code> $ cd yourappz </code>

2. package.json을 만드세요
   > <code> $ npm init </code>

3. 현재 워크스페이스에 Express를 설치하세요
   > <code> $ npm install express --save </code>

   > <code> $ npm install express --no-save </code>
 
 4. entry point 파일에 아래와 같이 작성하세요.
      ```javascript
      const express = require('express')
      const app = express()
      const port = 3000       

      app.get('/', (req, res) => {
         res.send('Hello World!')
      })

      app.listen(port, () => {
         console.log(`Example app listening at http://localhost:${port}`)
      })
      ```
        
5. 로컬 환경에서 실행해보세요.
   > <code> $ node entryfile.js