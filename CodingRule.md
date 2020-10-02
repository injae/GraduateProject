# Coding 규칙

<!---
. 간단한 코딩 규칙
. 필요하다고 생각하는 규칙은 추가하신 후 알려주면 코딩에 반영할게요.
-->
1. class는 CamlCase를 활용한다.
2. function들은 snace_case를 사용하여 작성한다.
3. member variable은 변수명뒤에 _를 붙여서 사용한다. 
4. namespace는 snake_case를 사용하여 작성한다.
5. 모든 멤버가 public인 class는 struct로 구현한다.
6. 기본적으로 모든 헤더는 namespace를 사용하여 감싼다. 
7. 최대한 함수이름은 그함수의 용도를 담고있는 이름(pdf이름 우선, 길이가 길어도 상관없다.)으로 작성하여 별도의 주석이 없는경우에도 사용할수 있게 작성하는것을 원칙으로한다.
8. 만약 함수이름만으로 설명이 어려운경우 부가적인 주석을 작성한다.
9. public header는 include폴더안에 작성을하며, private header는 .cpp 파일과 함께 작성한다.

```cpp
namespace test {
    class ClassName {
    public:
        /// 
        void test_function(int a, int b_b) {
        }
    private:
        std::string test_;
    };
}
```
