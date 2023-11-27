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

## FileSystemStore class & InMemoryStore class
두 클래스는 모두 데이터를 저장하고 관리하는 함수들이 선언된 Store 인터페이스를 구현한 클래스이다. FileSystemStore 클래스는 파일 입출력 스트림 클래스를 활용하여 파일 시스템에 데이터를 저장하는 방식이고, InMemoryStore 클래스는 map을 활용하여 메모리 상에서 데이터를 저장하고 관리하는 방식이다. 이 오픈소스에서는 아래에서 설명할 Wallet 클래스의 필드로 InMemoryStore 클래스의 객체를 사용하고, main에서 FileSystemStore 클래스를 사용하여 실제 데이터를 저장하였다.

FileSystemStore 클래스

    import java.io.File;    //C++의 include와 같은 역할 (라이브러리를 포함시켜 해당 라이브러리의 리소스를 사용할 수 있도록 함)
    import java.io.FileInputStream;
    import java.io.FileNotFoundException;
    import java.io.FileOutputStream;
    import java.io.IOException;
    import java.io.OutputStream;
    import java.io.UnsupportedEncodingException;
    import java.nio.file.Paths;
    import java.util.ArrayList;
    import java.util.Collections;
    
    public class FileSystemStore implements Store { //Store 인터페이스를 상속받아 구현하는 FileSystemStore 클래스 (Store 인터페이스는 Store.java에 있음)
    
        static private final String fileExtension = ".id";  //wallet에 데이터를 저장하고자 할 때, 저장할 파일의 확장자를 나타내는 변수
    
        private String path;
    
        public FileSystemStore(String path) {   //생성자 - 경로를 받아 디렉토리를 만들고 그 경로를 path변수에 저장
            File f = new File(path);
            f.mkdirs();
    
            this.path = path;
        }
    
        @Override
        public boolean put(String label, String content) {  //put 함수 오버라이딩 - 데이터를 넣을 파일명(label)과 넣을 데이터(content)를 입력으로 받아 데이터 넣기 결과를 bool값으로 반환
            boolean ret = false;
            OutputStream out = null;
            try {
                out = new FileOutputStream(getFilename(label)); //파일을 출력스트림에 올려 write를 할 수 있도록 함.
                out.write(content.getBytes());  //write할 데이터를 byte형식(1바이트 크기 정수 자료형)으로 반환하여 출력 스트림에 write
                ret = true;
            } catch (IOException e) {   //예외 처리
                e.printStackTrace();
                ret = false;
            } finally {
                try {
                    out.close();
                } catch (IOException e) {   //예외 처리
                    e.printStackTrace();
                }
            }
            return ret;
        }
    
        @Override
        public String get(String label) {   //wallet의 데이터를 저장할 파일의 파일명을 string형식으로 반환
            return readToString(getFilename(label));
        }
    
        @Override
        public ArrayList<String> list() {     //현재 경로의 파일(디렉토리)의 내부 파일들의 파일명 및 확장자를 출력하고 각 파일의 이름들을 목록화하여 반환하는 함수
            ArrayList<String> labels = new ArrayList<String>();
    
            File d = new File(this.path);
            if (d.isDirectory()) {      //path 경로의 파일이 디렉토리일 경우 아래의 블록을 실행
                String files[] = d.list();      //디렉토리의 파일 리스트를 string 배열에 저장
                for (String f : files) {    //각 파일들에 대하여 전체 파일명을 출력하고 파일명과 확장자를 분리해서 출력한 뒤, labels객체에 파일의 이름을 추가
                    System.out.println("file: " + f);
                    String[] strArray = f.split("\\."); //점(.)을 기준으로 문자열을 자르기 (파일명과 확장자를 분리하기 위함)
                    if (strArray.length == 2) {
                        String filename = strArray[0];
                        String extension = "." + strArray[1];
                        System.out.println("filename: " + filename + ", ext: " + extension);    //파일명과 확장자를 분리해서 출력
                        if (extension.equals(fileExtension)) {  //현재 파일의 확장자가 wallet의 저장소용 확장자와 동일하다면 list객체에 파일명을 추가
                            labels.add(filename);
                        }
                    }
                }
            }
    
            Collections.sort(labels);   //목록화한 파일명들을 알파벳 순으로 정렬
            return labels;
        }
    
        @Override
        public boolean exists(String label) {   //wallet의 데이터를 저장할 파일이 존재하는지 여부를 bool값으로 반환
            File f = new File(getFilename(label));
            return f.exists();
        }
    
        @Override
        public boolean remove(String label) {   //wallet의 데이터를 저장할 파일을 삭제
            File f = new File(getFilename(label));
            return f.delete();
        } 
    
        private static String readToString(String fileName) {  //파일명을 입력으로 받아 파일의 내용을 입력스트림의 read함수로 읽어 저장하고 이를 URF-8형식으로 인코딩하여 string형식으로 반환
            String encoding = "UTF-8";  
            File file = new File(fileName);  
            Long filelength = file.length();  
            byte[] filecontent = new byte[filelength.intValue()];  
            try {  
                FileInputStream in = new FileInputStream(file);  //파일을 읽어들이기 위해 입력스트립에 올리기
                in.read(filecontent);   //read 함수로 파일을 읽어들인 뒤 filecontent변수에 읽어들인 것을 저장
                in.close();  
            } catch (FileNotFoundException e) {  
                e.printStackTrace();  
            } catch (IOException e) {  
                e.printStackTrace();  
            }  
    
            try {  
                return new String(filecontent, encoding);   //파일의 데이터와 인코딩 형식을 String타입으로 변환하여 반환
            } catch (UnsupportedEncodingException e) {  
                e.printStackTrace();  
                return null;  
            }  
        }
    
        private String getFilename(String label) {  //wallet의 데이터를 저장할 파일의 파일명을 입력으로 받아 해당 파일의 경로, 파일명, 확장자를 모두 합친 string 문자열을 반환
            return Paths.get(this.path, label).toString() + fileExtension;
        }
    
    }

InMemoryStore 클래스

    import java.util.ArrayList;
    import java.util.Collections;
    import java.util.HashMap;
    import java.util.Map;
    import java.util.Set;
    
    public class InMemoryStore implements Store {   //Store인터페이스를 상속받아 구현하여, 데이터를 메모리 내의 맵을 사용하여 저장하고 관리하는 InMemoryStore클래스
        private Map<String, String> storage;    //label를 키로 사용하여 content라는 데이터를 저장하기 위한 맵 객체
    
        public InMemoryStore() {    //맵 객체를 할당 및 생성하는 생성자
            storage = new HashMap<String, String>();
        }
    
        @Override
        public boolean put(String label, String content) {  //입력으로 받은 데이터를 맵 객체에 저장하는 함수
            storage.put(label, content);
            return true;
        }
    
        @Override
        public String get(String label) {   //입력으로 받은 label에 해당되는 value값을 반환하는 함수
            return storage.get(label);
        }
    
        @Override
        public ArrayList<String> list() {   //데이터 목록의 모든 label을 목록화하여 반환하는 함수
            ArrayList<String> keys = new ArrayList<String>();   //데이터 목록을 저장할 리스트 객체
            Set<String> keySet = storage.keySet();  //keySet()을 이용하여 모든 key값(label)을 가져와 저장
            for (String s : keySet) {   //keys 객체에 가져온 key값들을 저장
                keys.add(s);
            }
            Collections.sort(keys);     //key값들을 알파벳 순으로 정렬
            return keys;
        }
    
        @Override
        public boolean exists(String label) {   //입력으로 받은 label에 해당되는 value값이 존재하는지 여부를 bool값으로 반환
            return storage.containsKey(label);
        }
    
        @Override
        public boolean remove(String label) {   //입력으로 받은 label에 해당되는 데이터를 삭제하는 함수
            storage.remove(label);
            return true;
        }
    }

Store 인터페이스

    import java.util.ArrayList;
    
    public interface Store {    //데이터를 저장, 반환, 목록화, 검색, 삭제하기 위한 Store인터페이스 
        boolean put(String label, String content);
        String get(String label);
        ArrayList<String> list();
        boolean exists(String label);
        boolean remove(String label);
    }

## Wallet class
이 오픈소스의 핵심인 wallet에 대한 정보를 저장하는 클래스이다. Store 클래스의 객체를 필드로 가지며, wallet에 데이터를 삽입, 반환, 삭제, 검색, 목록화하는 메서드를 정의한다.

    import java.util.ArrayList;
    
    import com.alibaba.fastjson.JSON;
    import com.alibaba.fastjson.JSONObject;
    
    public class Wallet {   //did wallet의 주요 기능인 wallet에 대한 클래스
        private Store store;    //Store인터페이스 타입의 객체
    
        public Wallet() {   //부모 객체를 자식 클래스로 메모리 할당
            this.store = new InMemoryStore();
        }
    
        public Wallet(Store store) {
            this.store = store;
        }
    
        public void put(String label, Identity id) {    //데이터를 저장할 파일명(label)과 did 정보에 대한 객체(content)를 입력으로 받아 store객체의 맵 변수에 추가
            String content = id.toString();
            store.put(label, content);
        }
    
        public Identity get(String label) {     //입력으로 받은 label에 해당되는 데이터를 가져와서 JSON 형식으로 파싱한 뒤 JSON 객체의 type값을 기반으로 Identity객체를 생성 및 반환하는 함수
            String content = store.get(label);
    
            JSONObject obj = JSON.parseObject(content); //데이터를 JSON형식으로 파싱 (JSON 파싱 : JSON 문자열의 구문을 분석하고 그 결과에서 JavaScript값이나 객체를 생성하는 것)
    
            String type = obj.getString("type");    //JSON객체의 type필드의 값을 얻기
    
            Identity id = null;
            switch (IdentityType.valueOf(type)) {   //type 유형에 따라 그에 맞는 Identity타입 객체를 id객체에 저장
                case Raw:
                    RawIdentity r = obj.toJavaObject(RawIdentity.class);
                    id = r;
                    break;
            
                default:
                    System.out.println("unsupported identity type: " + type);   //이 오픈소스에서는 Raw타입의 유형만 다루므로, 나머지 유형은 에러 처리
                    break;
            }
    
            return id;
        }
    
        public void remove(String label) {  //wallet의 저장소에서 입력을 받은 label에 해당되는 데이터를 삭제하는 함수
            store.remove(label);
        }
    
        public boolean exists(String label) {   //wallet의 저장소에서 입력을 받은 label에 해당되는 데이터가 존재하는지 여부를 bool값을 반환하는 함수
            return store.exists(label);
        }
    
        public ArrayList<String> list() {   ////wallet의 저장소에 저장된 데이터들의 label 목록을 반환하는 함수
            return store.list();
        }
    }

## main class
위에서 정의한 클래스들을 직접 테스트한다. 키의 id, 개인키, 공개키, did 값은 모두 임의의 값을 사용하였으며, 실행을 통해 실제로 디렉토리와 파일이 생성되고 데이터가 올바르게 저장됨을 확인할 수 있었다.

    import java.util.ArrayList;
    
    public class main {
        public static void main( String[] args )
        {
            Wallet w = new Wallet(new FileSystemStore("./wallet"));    //입력으로 받은 경로 위치에 디렉토리를 생성
    
            String keyID = "keys-1";
            String privateKeyHex = "a889f4da49ff8dd6b03d4334723fe3e5ff55ae6a2483de1627bec873b0b73e1e86eabd6abce2f96553251de61def0265784688ff712ce583621a5b181ef21639";
            String publicKeyHex = "86eabd6abce2f96553251de61def0265784688ff712ce583621a5b181ef21639";
            Key key = new Key(keyID, KeyType.Ed25519, privateKeyHex, publicKeyHex);     //키의 식별자, 유형, 개인키, 공개키를 입력으로 받아 Key타입 객체 생성
    
            String did = "did:example:3dda540891d14a1baec2c7485c273c00";    //임의의 did 변수
            RawIdentity rawIdentity = new RawIdentity(did, key);    //did변수와 key객체를 포함하는 RawIdentity타입의 객체 생성
    
            w.put("User1", rawIdentity);    //파일명(label)이 User1이고 파일의 내용(content)이 rawIdentity변수인 파일을 생성하고 wallet 디렉토리에 저장
    
            ArrayList<String> list = w.list();  //wallet에 포함된 label 목록을 저장하기 위한 리스트 객체
            for (String label: list) {
                Identity identity = w.get(label);
                if (identity != null && identity instanceof RawIdentity) {    //identity(did 정보)가 존재하고 RawIdentity 클래스의 인스턴스 일 경우 아래의 코드를 동작함
                    RawIdentity rid = (RawIdentity)identity;    //Identity(부모)타입의 객체를 RawIdentity(자식)타입으로 형변환
                    System.out.println(rid.getId());    //did의 식별자 출력 (아마 did 이름으로 추정)
                    System.out.println(rid.getType());  //did의 타입 출력 (아마 Raw로 추정)
    
                    Key k = rid.getKey();   //키에 대한 정보 저장
                    System.out.println("Key: ");    //여기부터 키의 정보들 출력
                    System.out.println(k.getId());
                    System.out.println(k.getType());
                    System.out.println(k.getPrivateKeyHex());
                    System.out.println(k.getPublicKeyHex());
                }
            }
        }
    }
