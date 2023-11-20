# Issuer

### 환경

운영체제 - Window 10

java version - java 17
```bash
> java -version
java version "17.0.8" 2023-07-18 LTS
Java(TM) SE Runtime Environment (build 17.0.8+9-LTS-211)
Java HotSpot(TM) 64-Bit Server VM (build 17.0.8+9-LTS-211, mixed mode, sharing)
```

Maven version - 3.8.6
```bash
> mvn -version
Maven home: D:\apache-maven-3.8.6
Java version: 17.0.8, vendor: Oracle Corporation, runtime: C:\Program Files\Java\jdk-17
Default locale: ko_KR, platform encoding: MS949
OS name: "windows 10", version: "10.0", arch: "amd64", family: "windows"
```

Spring-boot version - 3.1.4

#### JAVA

#### Maven

##### Maven Wrapper

```bash
> mvn -N io.takari:maven:wrapper
```

#### Spring-boot

### 실행

- Maven 사용 시

```bash
> mvn spring-boot:run
```

- Maven Wrapper 사용 시 

```bash
// mvnw 경로에서 실행
> mvnw.cmd spring-boot:run
```

  - Maven Wrapper가 실행되지 않을 경우 .mvn 폴더가 있는지 확인

