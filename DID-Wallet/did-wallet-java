# did-wallet-java

    package com.gfacloud.did;
    
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
            RawIdentity rawIdentity = new RawIdentity(did, key);    //did변수와 key객체를 이용하여 RawIdentity타입의 객체 생성
    
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

