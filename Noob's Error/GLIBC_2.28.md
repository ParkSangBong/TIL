## 에러 로그

```bash
node /lib/x86_64-linux-gnu/libc.so.6 version `GLIBC_2.28′ not found (required by node)
```

## 발생 원인

### 실행환경은 AWS EC2 우분투 18.04에서 초기 세팅을 진행하면서 노드를 설치 후 설치 확인을 진행하다가 발생하였다. 실행 중인 것과 다른 우분투 릴리스용으로 컴파일된 노드 버전이 설치되어 있어서 발생할 수 있다고 한다. (정확히 파악하지 못했다...)

## 검색 했던 키워드
- node /lib/x86_64-linux-gnu/libc.so.6 version `GLIBC_2.28′ not found (required by node)
- ec2 node: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.28' not found (required by node)

## 해결방법 

### 출처 : https://stackoverflow.com/questions/72921215/getting-glibc-2-28-not-found
- ### sudo apt-get remove nodejs
- ### nvm install 16.15.1

### Node.js를 삭제 후 낮은 버전(LTS)을 설치하여 해결