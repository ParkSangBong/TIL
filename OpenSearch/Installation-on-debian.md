# **************************** 공 사 중 **************************** #

# Install OpenSearch on debian

## INDEX
>
> ### 1. [OpenSearch](#opensearch)
>
> ### 2. [OpenSearch Dashboards](#install-opensearch-dashboards)

<br>

## OpenSearch

- ### 1. 설치

  - [다운로드 링크](https://opensearch.org/downloads.html)에서 자신의 운영체제에 맞는 설치 파일을 내려받는다.
  - debian 기준

    ```
    # x64
    sudo dpkg -i opensearch-2.8.0-linux-x64.deb
      
    # arm64
    sudo dpkg -i opensearch-2.8.0-linux-arm64.deb
    ```

  - 부팅시 서비스를 실행시켜주는 설정을 한다.

    ```
    sudo systemctl enable opensearch
    ```

  - OpenSearch 서비스를 실행시킨다.

    ```
    sudo systemctl start opensearch
    ```

  - OpenSearch 서비스 상태를 확인한다..

    ```
    sudo systemctl status opensearch
    ```

<br>

- ### 2. 테스트

  - 9200 포트에 요청을 날려본다.

    ```
    curl -X GET https://localhost:9200 -u 'admin:admin' --insecure
    ```

  - 정상적으로 설치되었다면 다음과 유사한 응답을 받을 수 있다.

    ```
    {
      "name":"hostname",
      "cluster_name":"opensearch",
      "cluster_uuid":"QqgpHCbnSRKcPAizqjvoOw",
      "version":{
        "distribution":"opensearch",
        "number":<version>,
        "build_type":<build-type>,
        "build_hash":<build-hash>,
        "build_date":<build-date>,
        "build_snapshot":false,
        "lucene_version":<lucene-version>,
        "minimum_wire_compatibility_version":"7.10.0",
        "minimum_index_compatibility_version":"7.0.0"
      },
      "tagline":"The OpenSearch Project: https://opensearch.org/"
    }
    ```

- ### 3. 환경설정

# Install OpenSearch Dashboards
