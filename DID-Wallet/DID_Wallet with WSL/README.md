# WSL에서 DID_Wallet 빌드

## 프로그램 설치
Visual Studio Code와 WSL(Ubuntu 20.04.6 LTS)를 설치한 뒤, 명령어를 사용하여 연동

ubuntu를 실행하여 다음의 명령어들을 입력

    $ sudo apt-get install build-essential gdb
    $ mkdir projects
    $ cd projects
    $ mkdir helloworld
    $ cd helloworld
    $  code .

## 개발 환경 구성
vscode 확장에서 Easy C++ Projects와 C/C++ 등의 도구를 설치한 뒤, C++ 프로젝트 생성
아래의 웹사이트를 참고하여 컴파일 및 디버깅에 대한 환경 설정

https://tiny-jay.tistory.com/5


## 개발 도구 추가
vscode에서 터미널을 열어 명령어를 통해 개발 도구들을 추가. 아래의 명령어들을 순서대로 실행

    $ sudo apt-get update
    $ sudo apt-get install make
    $ sudo apt-get install build-essential gdb
    $ sudo apt-get install nlohmann-json3-dev
    $ sudo apt-get install git
    $ sudo apt-get install rustc
    $ sudo apt-get install cargo

## C++ 소스 코드 작성
기존에 Visual Studio에서 작성한 DID_Wallet의 소스 코드들을 vscode의 src 디렉토리에 복사

## didkit 라이브러리 빌드
didkit 깃허브 오픈소스에서 제공하는 명령어들을 사용하여 didkit 라이브러리를 빌드. 터미널에서 아래의 명령어들을 순서대로 실행

    $ curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
    $ git clone https://github.com/spruceid/didkit.git
    $ git clone https://github.com/spruceid/ssi ../ssi --recurse-submodules
    $ cd didkit
    $ cargo build
    $ cd didkit/lib/c
    $ make -C ../ ../target/release/libdidkit.so

2번째 명령어로 깃허브를 클론하면 didkit라는 디렉토리가 생성되며, 마지막 명령어로 라이브러리를 빌드하면 didkit/target 디렉토리가 생성됨. target 디렉토리에 didkit.h라는 헤더파일이 포함되어 있음.

## 컴파일 경로 추가
외부 파일인 didkit.h를 같이 컴파일하기 위해 .vscode/c_cpp_properties.json 파일의 includePath 속성에 다음과 같이 경로를 추가

    "includePath": [
        "${workspaceFolder}/**",
        "/home/shuby/didkit/target"     //이 부분을 추가
    ],






