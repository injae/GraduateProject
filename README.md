# 졸업 프로젝트 구현용 예제

2020년 가을학기 졸업 프로젝트의 구현에 적용되는 Big Integer Library의 하나인 [openssl](https://www.openssl.org)에서 제공되는 `<openssl/bn.h`과 `openssl/rand.h`를 이용하여 구현하는 간단한 예제를 설명한다.

openssl은 기술적인 이유에 의하여 ANSI C로 구현되어 있으나, 본 예제에서는 Warpper Class를 만들어 C++ (정확하게는 std=c++11) 형식으로 구현한다.

## 설정
* openssl에서 제공하는 Big Number 연산을 위한 Funtion Prototype은 Openssl [설명서](https://www.openssl.org/docs/man1.0.2/man3/bn.html)를 참고한다. Install하는 방법은 여러 사이트에서 소개되었기 때문에 생략한다.
* [cmake](https://cmake.org)의 사용법은 안다고 가정한다. 시작하기엔 [여기](https://eunmink.tistory.com/6)부터 가보면 누구나 할 수 있다.
    - cmake는 `.dmg` 형태의 바이너리로 설치하는데, 설치에 관하여 상세하게 설명된 여러 사이트가 있으며 macOS에 설치하는 방법은 [여기](https://tudat.tudelft.nl/installation/setupDevMacOs.html) 정도가 추천할만 하다.
* Github의 `pull & push`등의 기본 Command도 안다고 가정한다. 필요하면 [간략히 설명한 사이트](https://medium.com/@pks2974/자주-사용하는-기초-git-명령어-정리하기-533b3689db81)를 방문하여 기억을 되살리고 시작해도 늦지 않다.
* [google tests](https://github.com/google/googletest)를 이용하면 좀 더 편리할 수 있으나, 향후 요청이 있는 경우 추가한다

## System 환경
- 운영체제: Apple  macOS Catalina 버전 10.15.2
- CPU: 3.7GHz 6코어 Intel Core i5
- M/M: 32GB 2667 MHz DDR4
- Programming 언어: clang++ version=11.0.0

## 사용법
1. openssl의 install
    - `bew install openssl`
    - Default installed folder: `/usr/local/Cellar/openssl@1.1/1.1.1g`이며 가능하면 기억해 놓는 것이 편리하다.
2. <span style="font-family: Courier;">./tests/test</span> 

<!---
<span style="font-family: Courier;">brew install openssl</span>
-->
