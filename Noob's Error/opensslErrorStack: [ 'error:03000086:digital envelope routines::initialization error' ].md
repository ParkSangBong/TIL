## 에러 로그
```bash
opensslErrorStack: [ 'error:03000086:digital envelope routines::initialization error' ],
  library: 'digital envelope routines',
  reason: 'unsupported',
  code: 'ERR_OSSL_EVP_UNSUPPORTED'
}

Node.js v18.12.1
[nodemon] app crashed - waiting for file changes before starting...
```

## 발생원인
- node의 버전이 맞지 않아 발생하는 에러

## 검색 했던 키워드
- opensslErrorStack: [ 'error:03000086:digital envelope routines::initialization error' ]


## 해결방법 

### 출처 : https://velog.io/@summereuna/error03000086digital-envelope-routinesinitialization-error-node.js-%EB%B2%84%EC%A0%84-%EC%97%90%EB%9F%AC
- ### nvm ls
- ### nvm use lts/fermium
- ### Node.js 버전을 변경하여 실행
