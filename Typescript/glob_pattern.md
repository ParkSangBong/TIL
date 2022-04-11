# 출처 https://ko.wikipedia.org/wiki/%EA%B8%80%EB%A1%9C%EB%B8%8C_(%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D)

### 컴퓨터 프로그래밍에서, 특히 유닉스 계열 환경에서 글로브(glob) 패턴은 와일드카드 문자로 여러 파일 이름의 집합을 지정한다. 이를테면 유닉스 명령어 mv *.txt textfiles/은 현재 디렉터리의 .txt로 끝나는 이름의 모든 파일을 textfiles 디렉터리로 이동(mv)시킨다. 여기에서 *는 모든 문자열을 가리키는 와일드카드이고 *.txt는 글로브 패턴이다. 그 밖의 일반적인 와일드카드는 하나의 문자를 가리키는 물음표(?)이다.

## 문법

|와일드카드|설명|예|일치|미일치|
|---|---|---|---|---|
|*|없는 것을 포함한 어떠한 수의 문자라도 일치|Law*|Law, Laws, 또는 Lawyer|GrokLaw, La, 또는 aw|
|*|없는 것을 포함한 어떠한 수의 문자라도 일치|*Law*|Law, GrokLaw, 또는 Lawyer.|	La, 또는 aw|
|?|어떠한 하나의 문자를 일치|?at|Cat, cat, Bat 또는 bat|at|
|[abc]|대괄호 안의 하나의 문자를 일치|	[CB]at|Cat 또는 Bat|cat 또는 bat|
|[a-z]|대괄호 안의 범위에 속하는 하나의 문자를 일치 (로케일에 따라 다름)|Letter[0-9]|Letter0, Letter1, Letter2 ... Letter9|Letters, Letter 또는 Letter10|