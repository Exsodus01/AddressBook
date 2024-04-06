![image](https://github.com/Exsodus01/AddressBook/assets/34214553/6dbf8f2f-83ee-41d7-aa08-362bfd62370a)

이름으로 txt를 탐색.
아직 중복 이름에 관한 처리를 하지 않음.



![image](https://github.com/Exsodus01/AddressBook/assets/34214553/bfde8220-163e-4750-b19d-63f6a6f31323)

노드를 추가하고 노드의 개수를 체크.
리스트가 빈 경우와 끝에만 추가.
특정 위치에 추가하는 함수는 미구현.

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/93a4b7de-2e9d-4b6c-8e7f-7ac4239bd9b5)

리스트를 모두 출력.


![image](https://github.com/Exsodus01/AddressBook/assets/34214553/f549284a-5a7b-4d56-9f95-f1f7a307e72f)


노드를 삭제하는데 단일 연결 리스트 형식이라 현재의 노드를 탐색하는게 아니라 다음 노드를 탐색해서 
비교하고 다음 노드가 타겟 노드가 맞으면 다른 포인터로 옮기고 현재의 노드에 다다음 노드를 이어붙이고 
옮겨둔 타겟노드를 삭제하는 방식.


![image](https://github.com/Exsodus01/AddressBook/assets/34214553/3161395f-be30-4c10-a583-de874adc18d8)

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/d598c4ef-745a-450d-a1b4-aedb67368dac)





1. 로드할 파일을 열어서 핸들을 준비.
2. 파일 사이즈를 미리 구해서 준비
3. 매핑 객체를 생성
4. 만들어둔 객체에 파일 매핑
5. 매핑된 객체를 읽어서 파싱

파싱하기 전까지 zero-copy로 구현.


![image](https://github.com/Exsodus01/AddressBook/assets/34214553/cae5691e-60a8-4df2-9579-10eb2fccc8f8)


원래는 readFile로 원하는 바이트 단위로 읽어서 iss를 이용해서 파싱.

어떤 바이트로 자를지에 대한 방안
1. 주소록을 만줄로 생성했으니 GetFileSize로 크기를 구해서 / 10000 으로 예측.
2. 바이트 단위로 공백과 개행이 나올때까지 읽어서 string append.
3. 메모리가 충분하다면 한방에 메모리에 올려서 처리.
4. 파일포인터로 핀 포인트로 확인.
5. 메모리 매핑
6. std::ifstream 사용해서 한줄씩 읽고 iss로 파싱

실제 구현은 나중에 비동기와 멀티스레드를 위해 메모리 매핑으로 구현.
