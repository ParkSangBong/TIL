# 클라이언트-서버 모델/아키텍처 (2-Tier Architecture)

## 리소스가 존재하는 곳과 리소스를 사용하는 앱을 분리시킨 것을 2티어 아키텍처, 또는 클라이언트-서버 아키텍처라고 부른다.

- ### 리소스를 사용하는 앱이 바로 "클라이언트"
- ### 리소스를 제공하는 곳을 바로 "서버"라고 부른다.

![클라이언트-서버 아키텍처](https://user-images.githubusercontent.com/25292654/186713678-616cb9f2-f3e7-4092-9201-71fb243e8948.png)

그림을 하나 더 보도록 하자.

![스크린샷 2022-08-26 오전 1 03 44](https://user-images.githubusercontent.com/25292654/186714448-ed917315-2c65-4869-919d-2e34348a5843.png)

### 클라이언트(손님)와 서버(서빙하는 사람)라는 단어의 어원을 떠올리면 보다 이해가 쉽다.

### 리소스에 접근하려는 앱은 카페로 치면 손님과 같다. 손님은 아메리카노를 획득하기 위해 리소스를 가지고 있는 점원에게 요청해야 한다. 손님의 요청에 따라 점원은 리소스(아메리카노)를 담아 응답한다.

<br>

### 이처럼 클라이언트와 서버는 요청과 응답을 주고받는 관계이다. 클라이언트-서버 아키텍처에서는 요청이 선행되고 그 후에 응답이 온다. 요청하지 않았는데 응답이 오는 경우는 없다.

<br>

# 3-Tier Architecture

### 보통 서버는 리소스를 전달해 줄 뿐, 리소스를 저장하는 공간은 데이터베이스라는 창고에 둔다. 이처럼 클라이언트-서버 아키텍처에 데이터베이스가 추가된 형태를 3-Tier Architecture라고 한다.