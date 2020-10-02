# 졸업 프로젝트 구현용 예제

2020년 가을학기 졸업 프로젝트의 구현에 적용되는 Big Integer Library의 하나인 [openssl](https://www.openssl.org)에서 제공되는 `<openssl/bn.h>`과 `<openssl/rand.h>`를 이용하여 구현하는 간단한 예제를 설명한다.

openssl은 기술적인 이유에 의하여 ANSI C로 구현되어 있으나, 본 예제에서는 Wrapper Class를 만들어 C++ (정확하게는 std=c++11) 형식으로 구현한다.

## 설정
* openssl에서 제공하는 Big Number 연산을 위한 Funtion Prototype은 Openssl [설명서](https://www.openssl.org/docs/man1.0.2/man3/bn.html)를 참고한다. Install하는 방법은 여러 사이트에서 소개되었기 때문에 생략한다.
* [cmake](https://cmake.org)의 사용법은 안다고 가정한다. 시작하기엔 [여기](https://eunmink.tistory.com/6)부터 가보면 누구나 할 수 있다.
    - cmake는 `.dmg` 형태의 바이너리로 설치하는데, 설치에 관하여 상세하게 설명된 여러 사이트가 있으며 macOS에 설치하는 방법은 [여기](https://tudat.tudelft.nl/installation/setupDevMacOs.html) 정도가 추천할만 하다.
* Github의 `pull & push`등의 기본 Command도 안다고 가정한다. 필요하면 [간략히 설명한 사이트](https://medium.com/@pks2974/자주-사용하는-기초-git-명령어-정리하기-533b3689db81)를 방문하여 기억을 되살리고 시작해도 늦지 않다.
* [google tests](https://github.com/google/googletest)를 이용하면 좀 더 편리할 수 있으나, 향후 요청이 있는 경우 추가한다
* mariadb와 openssl부분은 brew를 사용하여 자동으로 설치되기때문에 현재 macos에서만 dependency를 자동으로 관리된다. 향후 멀티플랫폼 빌드 요청이 있는경우 추가한다.
* 대부분의 구현은 pdf에 있는 내용과 거의 일치하는 이름으로 구현되었다.
* networking과 protocol은 ZeroMQ와 json을 이용하여 구현하였다.
* 데이터베이스 테스트값은 실행하였을때 테이블이 비어있다면 자동으로 추가된다.
* 별도의 dependency들은 cmake를 이용하여 자동으로 설치되기때문에 cmake와 c++ compiler만 있으면 작동된다.
* socket통신은 기본적으로 ssl로 감싸지 않았기때문에 향후 요청이 있는 경우 추가한다.

## System 환경
- 운영체제: Apple  macOS Catalina 버전 10.15.2
- CPU: 3.7GHz 6코어 Intel Core i5
- M/M: 32GB 2667 MHz DDR4
- Programming 언어: clang++ version=11.0.0

## 사용법
```console
# 클린하게 관리할수있는 cmake debug build 과정 release build를 하려면 Debug 부분을 Release로 변경하면 된다.
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . --config Debug 
cd Debug

# 별도의 터미널에서
./server
# 별도의 터미널에서
./client
```
## 실행결과
### server
```console
❯ ./server
gp2020fall: connected
infecotrs: {"1", "4"}
```
### client
```console
❯ ./client
gp2020fall: connected
infecters[2]:{"1", "4"}
finish
```


<!---
<span style="font-family: Courier;">brew install openssl</span>
-->
