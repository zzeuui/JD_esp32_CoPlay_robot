### ESP32 아두이노 개발환경 셋업 
JD 로봇 플랫폼에 사용되는 ESP32 마이크로컨트롤러는 아두이노 개발환경과 아두이노 코딩언어인 C++을 사용하여 코딩이 가능합니다. 그래서 먼저 ESP32 아두이노 개발환경을 설치합니다. 

#### ESP32 보드 패키지 URL 등록 
일반적으로 아드이노 IDE를 설치하면 아두이노 우노 같은 AVR 계열의 MCU를 코딩하고 컴파일 해주는 개발환경만 설치됩니다. 아두이노 우노에 사용되는 AVR 계열의 MCU와 ESP32는 전혀 다른 마이크로컨트롤러 입니다. 아두이노 IDE는 AVR계열 MCU 말고도 다른 종류의 MCU로 개발을 할 수 있습니다. 다만 아두이노 IDE에서 ESP32로 코딩을 하려면 몇가지 소프트웨어를 설치해야 합니다. 제일 먼저 해야 할 것은 ESP32 보드 패키지를 설치할 URL을 등록 합니다.  ESP32 보드 패키지를 설치하기 위해서 아두이노 IDE에서 ***파일 -> 기존설정*** 을 선택합니다. 그러면아래 그림과 같이 기본설정 윈도창이 열립니다. 

![아두이노_추가보드관리자_URL](https://github.com/JD-edu/JD_robot_platform/assets/96219601/efedb533-9a73-4792-8845-529884fd84f1)

여기에서 추가 보드 관리자URL 아이콘을 찾습니다. 노란색 원으로 표시된 이 아이콘을 아이콘을 클릭합니다. 그러면 아래 그림과 같이 추가 보드 관리지 URL 입력 창이 열립니다. 

![추가보드관리자_URL](https://github.com/JD-edu/JD_robot_platform/assets/96219601/c1360223-660b-49ee-85c5-f6d967b2cc21)

"각 항에 하나씩 추가 URL을 입력하세요" 문구 밑에 입력창에 ESP32 보드 패키지 주소를 입력합니다. 주소는 다음과 같습니다. 

<pre><code>
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
</code></pre>

#### ESP32 보드 패키지 설치 
ESP32 보드 패키지 URL을 등록햇으면 이제 우리는 ESP32 개발환경을 다운로드 받을 수 있게 되었습니다. 다음에는 실제로 ESP32 보드 패키지를 다운로드해서 설치해 보도록 하겠습니다. ***도구 -> 보드 -> 보드 매니저***  를 선택합니다. 보드 매니저를 실행하면 다음과 같이 아두이노 IDE 좌측에 보드 매니저가 실행이 됩니다. 보드매니저 우족 노란색 원에 'esp32'라고 입력해서 EPS32 보드 패키지를 검색합니다. 

![보드매니저_esp32](https://github.com/JD-edu/JD_robot_platform/assets/96219601/0cb1e666-fcd4-4a14-97fe-35d2397f6d54)

몇개의 검색 결과 중에서 흰색 원으로 표시된 Espressif의 ESP32 보드 패키지를 선택하고, 역시 흰색 원에 있는 녹색 "설치" 버튼을 클릭해서 보트 패키지를 설치하면 됩니다. Espressif는 ESP32 마이크로컨틀러를 제작한 회사이름 입니다. 이 회사에서 컴파일러 등 보드 패키지를 제공합니다. 

#### ESP32 DevKit보드 선택 
ESP32는 다양한 모듈과 보드가 존재하기 대문에 우리가 사용하려는 ESP32 DevKit를 찾아서 선택해 주어야 합니다. ESP32 DevKit 보드를 선택하는 방법은 다음과 같습니다. ***도구 -> 보드***  를 선택하면 이전에는 없었던 ESP32 보드 항목이 추가되어 있습니다. 이중에서 우리가 선택할 보드는 ESP32 Dev Module 입니다. 이것을 선택해 주면 됩니다. 

![esp32_dev_module_선택](https://github.com/JD-edu/JD_robot_platform/assets/96219601/22633c4a-91a9-42ac-98d7-af537c6cefa4)

이렇게 해서 ESP32 개발환경 및 ESP32 DevKit 선택이 끝이 났습니다. 

### 에제 코드를 돌려보기 
이제 개발환경 셋업이 끝이 났으므로 예제 코드를 한번 돌려보기로 하겠습니다. 깃허브에서 다운로드 받은 소스코드 중에서 "100_get_started" 폴더에 101_get_started.ino 소스코드 파일을 아두이노 IDE ***파일 -> 열기***  로 엽니다. 이 소스코드는 로봇의 모터를 전진 -> 후진 -> 좌회전 -> 우회전 구동 합니다. 

#### 에제 코드 살펴보기
"100_get_started.ino" 코드는 다음과 같이 구성되어 있습니다. 

```C
// install TB6612FNG library
//https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG

#include <TB6612FNG.h>

#define MSLEEP  16
#define IA1     14
#define IB1     12
#define PWM1    13
#define IA2     27
#define IB2     26
#define PWM2    25
#define IA3     17
#define IB3     5
#define PWM3    18
#define IA4     4
#define IB4     2
#define PWM4    15

Tb6612fng motors1(16, 14, 12, 13, 26, 27, 25);
Tb6612fng motors2(16, 5, 17, 18, 4, 2, 15);
void go_forward(){
  Serial.println("forward");
  motors1.drive(1);
  motors2.drive(1);
}

void go_backward(){
  Serial.println("backward");
  motors1.drive(-1);
  motors2.drive(-1);
}

void turn_right(){
  Serial.println("right");
  motors1.drive(1);
  motors2.drive(-1);
}

void turn_left(){
  Serial.println("left");
  motors1.drive(-1);
  motors2.drive(1); 
}

void stop(){
  Serial.println("stop");
  motors1.drive(0);
  motors2.drive(0);
  delay(200);
}

void setup() {
  Serial.begin(115200);
  Serial.print("motor test start...");

  motors1.begin();
  motors2.begin();

}

void loop() {
    go_forward();
    delay(1000);
    go_backward();
    delay(1000);
    turn_left();
    delay(1000);
    turn_right();
    delay(1000);
}
```

#### 모터 드러이버 라이브러리 설치 
로봇을 동작시키기 위해서는 먼저 모터 동작시키는 라이브러리를 설치해야 합니다. 설치해야 할 라이브러리의 URL은 다음과 같습니다. 

<pre><code>
https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG
</code></pre>

라이브러리를 설치하기 위해서는 먼저 위 URL에 가서 라이브러리 코드를 다운로드 받습니다. 다운로드 받는 방법은 다음 사이트에서 녹색 code 버튼을 클릭해서 라이브러리 zip 압축 파일을 다운로드 받습니다. 

![image](https://github.com/JD-edu/JD_robot_platform/assets/96219601/93eb62de-3907-4613-b287-e8c0623c81c9)

다은로드 받은 라이브러리 코드를 사용자 PC에 아두이노 IDE가 설치된 폴더에서 "libraries" 폴더에 카피합니다. 일반적으로 아두이노 IDE가 설치된 폴터는 다음과 같습니다. 

<pre><code>
C:\Users\user\Documents\Arduino\libraries
</code></pre>

사용자의 PC환경에 따라 다르지만 대부분 "문서" 폴더에 Arduino폴데어 설치되어 있습니다. 

#### 예제 코드 빌드 및 업로드 
이제 코드를 빌드하고 ESP32 DevKit 보드로 업로드 해야 합니다. 다음 그림과 같이 ***도구 -> 포트***  메뉴를 통해해서 업로드할 포트를 정해 주어야 합니다. 가능하면 컴퓨터에 ESP32 DevKit 하나만 남겨놓고 작업하는 것이 좋습니다. PC에 ESP32 DevKit가 연결되어 있다면 포트가 빨간색 원처럼 나타날 것 입니다.  

![esp32_업로드포트](https://github.com/JD-edu/JD_robot_platform/assets/96219601/dabd3899-7640-4747-97f5-9d49cd1cf1f7)

준비가 다 되었으면 도구 메뉴를 통해서 다음 그림과 같이 셋팅이 되었는지 다시 한번 확인합니다. 보드는 "ESP32 Dev Module"로 셋팅이 되어있어야 합니다. 포트는 각 PC마다 다르지만 해당하는 포트가 연결되어 있어야 합니다(얘: COMXX). 파란색 사각형 처럼 정보가 표시되어야 합니다. 특뱔한 일이 없다면 이 파란색 사각형 내부의 정보는 건드리지 않아도 됩니다. 

![esp32_업로드_셋팅](https://github.com/JD-edu/JD_robot_platform/assets/96219601/2ff5bb64-12fc-477e-9e33-37ac1755344c)

모든 셋팅이 완료되면 다음과 같이 업로드 아이콘을 클릭해서 컴파일 및 업로드를 실행합니다. 업로드 버튼은 다음 그림의 파란색 원의 화살표 모양의 버튼 입니다. 

![esp32_업로드_버튼](https://github.com/JD-edu/JD_robot_platform/assets/96219601/b2b1e5b5-0123-4f96-9d05-c610f3f3c0a4)

업로드가 실행이 되면 컴파일과 업로드를 진행합니다. 컴파일 상황과 업로드 상태가 아두이노 IDE 아래 정보창에 다음과 같이 표시됩니다. 다음 그림과 같은 메시지가 표시되면 업로드가 완료 된 것 입니다. 

![esp32_컴파일_업로딩](https://github.com/JD-edu/JD_robot_platform/assets/96219601/9b44dbb4-dd78-4342-8775-2e51d8a430d1)

이제 업로드가 완료되면 코드가 동작되면서 로봇이 전진 후진 좌회전 우회전을 반복하는 것을 볼 수 있습니다. 
