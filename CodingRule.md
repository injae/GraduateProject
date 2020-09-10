# Coding 규칙

<!---
. 간단한 코딩 규칙
. 필요하다고 생각하는 규칙은 추가하신 후 알려주면 코딩에 반영할게요.
-->

### Class
1. Class 이름은 **_ClassName**
    >~~~cpp
    > class _ClassName
    > {
    >   ...
    > };
    >~~~
2. class의 member function과 변수들
    * Variables:
        - public: **_PublicName**,
        - protected: **ProtectedName_**,
        - private: **PrivateName__**
        >~~~cpp
        > template <class T>
        > class _ClassName
        > {
        > ///
        > public:
        >     function declarations;
        > ///
        > public:
        >     int32_t _a;       /// public
        >     std::string b_;   /// protected
        >     T c__;            /// private
        > };
    * Functions: 위와 같이하고 가능하면 **동사** 소문자로 시작합니다.
        - public: **_doSomething(...)**
        - function의 구현은 다음 정도의 모양을 유지하도록 사용했습니다.
        > ~~~cpp
        > return_type
        > _ClassName::_doSomething(arguments_list)
        >{
        >   uint32_t a = 0;
        >   uint8_t* b = nullptr;
        >   return_type res;
        >  
        >   ...
        >   return res;
        >}
        > ~~~
        - 함수 내부는 적당히 단락을 구분지어 주면서

## Some <span style="font-family:courier">Keywords</span>
1. **c++11** 이후 버전에서 지원하는 keyword 쓰면 됩니다.
2. **if**
    >~~~cpp
    > if (a == b) {}
    >     statement;
    > }
    >~~~

3. **for** and **while**
    >~~~cpp
    > for (uint32_t i = start; i < end; i++) {
    >     statement;
    > }
    >~~~
    이나
    >~~~cpp
    > uint32_t i = 0;
    > while (i < Bnd) {
    >     statement;
    > }
    >~~~
    또는
    >~~~cpp
    > #inclide <algorithm>
    > ...
    > {
    >     ...
    >     for_each (begin, end, obj);
    >     ...
    > }
    >~~~
    를 써도 되고
    >~~~cpp
    > {
    >     ...
    >     for_each (begin, end, doSomething);
    >     ...
    > }
    >~~~
4. intrinsic type외에 `typedef`하기 전에 `#include <cstdint>`를 먼저 살펴보고 있으면 여기 미리 정의되어 있는 type들을 사용하길 권합니다.


## Comments
1. **Doxygen**을 따를 정도면 충분해 보여서; 최대한 정성껏 주석을 추가했습니다 :wink:
2. class는
    > ~~~cpp
    > /**
    >  * @class _ClassName
    >  * @brief 적당한 설명 (너무 형편없지만 않으면, 없는것 보다는 나은 듯 :-)
    >  *
    >  */
    >~~~

3. function은
    > ~~~cpp
    > /**
    >  * @fn    _doSomething(...)
    >  * @brief 적당한 설명
    >  * @param arg1
    >  *
    >  */
    >~~~
4. `#define`과 특별한 variable들은 용도 설명만 간단히 설명했습니다.
    >~~~cpp
    > /// @def    SOME_LITERAL
    > /// @brief  what for?
    > #define SOME_LITERAL    1000
    >
    > /// @var    _cPi
    > /// @brief  what for?
    > static const uint32_t   _cPi  =  3.141592;
    >~~~
5. 자잘한 것은 알아서 debugging만 편하면 적당히 알아서 하시면...:shipit:
