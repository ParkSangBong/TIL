# 터미널에서 hostname이 192로 나오는 현상
### 192가 내부망의 첫번째 옥텟으로 생각했는데 대충 맞는거 같다. 발생한 환경은 스터디 중 스터디 공간의 와이파이가 느려 핫스팟을 켜서 인터넷에 접속한 상태에서 터미널을 켰을 때 발견하였다.
<img width="330" alt="스크린샷 2023-10-14 오전 10 40 28" src="https://github.com/ParkSangBong/shiny-sniffle/assets/25292654/f20f5af4-d509-4533-b451-153970df3703">

### 해결을 위해 구글링을 하다가 찾은 해결법 -> https://stackoverflow.com/questions/67785772/mac-terminal-shows-myname192-instead-of-mynamemyname-mac-pro
```
scutil --get HostName
```
### 위 커맨드라인을 입력해 내 컴퓨터에서 이용가능한 HostName이 없을 때, DNS 혹은 DHCP 서버에서 가져온다고 한다. 그 상황일 때 192가 불편하다면 
If there's no HostName available, what you see is probably coming from the DNS or DHCP server.
```
sudo scutil --set HostName 'yourHostName'
```
### 위 커맨드라인으로 지정하고 싶은 HostName을 설정할 수 있다.
