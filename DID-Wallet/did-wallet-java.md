# did-wallet-java
did-wallet-java는 java언어 기반으로 작성된 did-wallet 코드로, wallet의 데이터가 파일 시스템에 저장되도록 구현하였다. Wallet의 생성 및 저장 방식 이외에 did 생성 등에 대해서는 다루고 있지 않는다.

## Key class
키에 대한 정보를 저장하는 Key 클래스이다. id, 유형, 개인키, 공개키에 대한 정보를 저장한다.
    
    public class Key {      //id, 유형, 개인키, 공개키 등 디지털 키에 대한 정보를 나타내는 Key클래스
        private String id;  //키의 식별자
        private KeyType type;   //키 유형
        private String privateKeyHex;   //개인키
        private String publicKeyHex;    //공개키
    
        Key(){}     //기본 생성자
    
        public Key(String id, KeyType type, String privateKeyHex, String publicKeyHex) {    //생성자
            this.id = id;
            this.type = type;
            this.privateKeyHex = privateKeyHex;
            this.publicKeyHex = publicKeyHex;
        }
        
        public void setId(String id) {  //여기부터 아래의 8개 함수 모두 4개의 필드에 대한 get/set 함수
            this.id = id;
        }
    
        public String getId() {
            return id;
        }
    
        public void setType(KeyType type) {
            this.type = type;
        }
    
        public KeyType getType() {
            return type;
        }
    
        public void setPrivateKeyHex(String privateKeyHex) {
            this.privateKeyHex = privateKeyHex;
        }
    
        public String getPrivateKeyHex() {
            return privateKeyHex;
        }
    
        public void setPublicKeyHex(String publicKeyHex) {
            this.publicKeyHex = publicKeyHex;
        }
    
        public String getPublicKeyHex() {
            return publicKeyHex;
        }
    
        @Override
        public String toString() {      //Identity 객체를 JSON기반 String형식의 문자열로 변환하여 반환
            return JSON.toJSONString(this);
        }
    }

키의 유형을 나타내는 KeyType은 키 유형들을 나열한 enum(열거형)이다.

    public enum KeyType {   //공개키의 유형에 대한 enum 클래스
        Ed25519("Ed25519"); //유일한 enum 열거형 값
    
        private final String name;
        KeyType(String name) {
            this.name = name;
        }
        public String getName() {
            return name;
        } 
    }

## Identity class & RawIdentity class
Identity 클래스는 did 정보를 저장하기 위한 추상 클래스로, did의 버전, 유형, id 등에 대한 정보를 저장한다. RawIdentity 클래스는 이 오픈소스에서 지원하는 Raw Identity Type 전용으로 구현된 클래스로, Identity 클래스를 상속받는다. RawIdentity 클래스는 Key 클래스의 객체를 필드로 가지는데, 이와 같이 did의 유형에 따라 필요한 필드나 메소드가 달라질 수 있기 때문에 Identity를 추상 클래스로 구현함과 동시에 Identity 클래스와 RawIdentity 클래스를 분리한 것으로 보인다.

Identity 클래스


    import com.alibaba.fastjson.JSON;
    
    public abstract class Identity {    //did의 기본 속성들을 나타내는 추상 클래스.
        private int version;    //did 버전
        private IdentityType type;  //did 유형
        private String id;  //did 식별자
    
        Identity() {}   //기본 생성자
    
        Identity(int version, IdentityType type, String id) {   //생성자
            this.version = version;
            this.type = type;
            this.id = id;
        }
    
        public int getVersion() {   //여기부터 아래의 6개 함수 모두 3개의 필드에 대한 get/set 함수
            return version;
        }
    
        public void setVersion(int version) {
            this.version = version;
        }
    
        public IdentityType getType() {
            return type;
        }
    
        public void setType(IdentityType type) {
            this.type = type;
        }
    
        public String getId() {
            return id;
        }
    
        public void setId(String id) {
            this.id = id;
        }
    
        @Override
        public String toString() {  //Identity 객체를 JSON기반 String형식의 문자열로 변환하여 반환
            return JSON.toJSONString(this);
        }
    }

RawIdentity 클래스

    public class RawIdentity extends Identity {     //Identity 클래스를 상속받는 RawIdentity 클래스
        static final private int version  = 1;  //버전을 나타내는 상수 (final은 더이상 재할당 할 수 없다는 의미로, 값이 고정됨을 의미)
    
        private Key key;
    
        RawIdentity() {}    //기본 생성자
    
        public RawIdentity(String id, Key key) {    //생성자
            super(version, IdentityType.Raw, id);   //super는 부모의 생성자를 호출하겠다는 것을 의미
            this.key = key;
        }
    
        public Key getKey() {   //key변수에 대한 get함수
            return key;
        }
    
        public void setKey(Key key) {   //key변수에 대한 set함수
            this.key = key;
        }
    }

did의 유형을 나타내는 IdentityType은 did 유형들을 나열한 enum(열거형)이다.

    public enum IdentityType {  //java의 enum은 주로 관련있는 상수값들을 그룹화 및 나열할 때 이용
        Raw("Raw");     //유일한 enum 열거형 값
    
        private final String name;
    
        IdentityType(String name) {
            this.name = name;
        }
    
        public String getName() {
            return name;
        }
    }

## 





