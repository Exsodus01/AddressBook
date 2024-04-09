![image](https://github.com/Exsodus01/AddressBook/assets/34214553/5124e51d-2fcf-4566-ac54-83d22136a76f)

DataNode를 상속받아 UserData클래스를 작성하고 UserList는 DataNode*를 다루는 방식으로 다형성을 구현
순수 가상 클래스인 DataNode를 상속받아 UserData , MovieData , MusicData 등 다양한 자료형을 UserList를 이용해 연결리스트로 만들어서 사용 가능.
이후 인터페이스에 Mode함수를 이용해 다른 컨테이너도 사용가능하게 업데이트 예정.

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/b5d31b23-ddf4-47cb-bf8c-26f4c606c7c8)

1. 사용자 메뉴 출력


![image](https://github.com/Exsodus01/AddressBook/assets/34214553/652289c5-cdbe-47d1-815d-07ebc804710a)


2. Add함수로 추가

   
![image](https://github.com/Exsodus01/AddressBook/assets/34214553/11047bd3-f1cf-4baa-a9be-2fa990a369e9)


3. LoadFile로 파일 불러오기

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/947b93c2-54c8-4516-8198-c7c5bee3e3f3)

4. Print로 목록 확인

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/897328e2-1608-4168-af9b-530d43d016c0)

5. Search로 탐색 (중복 포함)

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/ab442383-605e-4f75-95f6-f422f9843727)

6. Remove노드로 삭제(중복포함) 처리 

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/6bada281-496c-4415-bbc4-41b1f40cd694)

7. 2번 인덱스 8950 삭제

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/33bbf72f-9490-49f3-a575-3281ca917e4d)

8. 4번 인덱스 6209 삭제

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/f0936ccc-158c-45e5-990b-90750c009eeb)

9. 삭제후 남은 노드 9999개 (기존 1번의 add와 불러온 10000개에서 2개 삭제처리)

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/3ac91edc-ab4b-472b-a8e0-c096df62e0f1)

10. Print로 확인시 남아있던 중복 키들은 노드의 마지막에 Add된걸 확인 가능

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/6bedf4aa-7acd-4617-a0ae-7b3efb4219ff)

11. 파일 생성시 이름 입력

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/447e815f-ed9f-470f-a9d0-f94b7ac0855b)

12. 파일로 생성완료

![image](https://github.com/Exsodus01/AddressBook/assets/34214553/be435d93-5e80-433f-87f4-811c37c6b7a3)

13. 종료시 자동으로 리스트가 삭제되어 삭제 완료 표시.

