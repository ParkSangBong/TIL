# 리포지토리 패턴

리포지토리 패턴은 데이터베이스와 같은 저장소를 다루는 로직을 데이터 레이어로 분리하여 핵심 비즈니스 로직에 집중할 수 있도록 한다.  
리포지토리는 인터페이스를 통해 데이터를 처리하도록 추상화되어 있으므로 필요할 경우 데이터 저장소를 변경하기 쉽다는 장점도 있다.  
Martin Fowler의 책 "엔터프라이즈 애플리케이션 아키텍처 패턴" 에서 리포지토리를 다음과 같이 기술한다.

> 리포지토리는 도메인 모델 계층과 데이터 매핑의 중간자 역할을 하며 메모리 내의 도메인 개체 집합에 대해서도 비슷한 방식으로 작업을 수행합니다. 클라이언트 객체는 쿼리를 선언적으로 빌드하고 리포지토리에 요청합니다. 개념적으로 리포지토리는 데이터베이스에 저장되는 객체 집합과 그것들에 대해 수행하는 작업을 캡슐화해서 영속화 계층에 더 가까운 방법을 제공합니다. 리포지토리는 또한 작업 도메인 및 데이터 할당 또는 매핑 간의 종속성을 명확하게 한 방향으로 구분하려는 목적을 지원합니다.

![리포지토리패턴](//TODO)

위 그림에서 비즈니스 로직을 처리하는 클라이언트는 직접 데이터 소스를 다루지 않는다.  
리포지토리를 활용하여 엔티티 객체를 영속화하고, 역시 리포지토리를 통해 데이터를 비즈니스 엔티티 개체로 전달받는다.  
영속화, 쿼리 요청과 응답을 가공하는 리포지토리는 데이터소스에 맞는 구현체를 가진다.  
즉, 데이터를 데이터베이스에 저장하기 적합하게 매핑을 하고 쿼리 결과를 클라이언트가 원하는 방식으로 가공한다.  
만약 데이터베이스를 MySQL에서 PostgreSQL로 변경하고자 한다면 클라이언트와의 인터페이스는 그대로 두고 구현부만 적합하게 변경하면 된다.