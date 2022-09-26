# Vjoy e pyautogui

Dicas para o vjoy e pyautogui

## vjoy

Nós utilizamos o pacote `pyvjoy` que possibilita controlarmos o `vjoy` via python. Ele é apenas uma camada de abstração do vjoy.

- https://github.com/tidzo/pyvjoy

Nós sugerimos vocês trabalharem com a `monitor` do vjoy aberto, para conseguirem depurar visualmente o que está acontecendo com o controle.

### Criando 

Criando um joystick

``` py
import pyvjoy
j = pyvjoy.VJoyDevice(1)
```

### Acionando um botão

Acionando o botão 15

``` py
j.set_button(15,1)
```

!!! info
    O vjoy mantém o valor mesmo com o programa reiniciado, se apertar o botão 15 e deixar ele apertado, da próxima vez que for usar o controle ele vai continuar apertado.

Soltando o botão 15

``` py
j.set_button(15,0)
```

!!! note ""
    Notem que o `j.set_button` recebe: `(buttonID,state)`

### Analógico

O vjoy possui várias [entradas analógicas](https://github.com/shauleiz/vJoy/blob/8111294ef89b25d35fa2617a62ce96d23275ab16/inc/public.h#L238), sendo as principais:

```
HID_USAGE_X
HID_USAGE_Y
HID_USAGE_Z
HID_USAGE_RX
HID_USAGE_RY
HID_USAGE_RZ
```

O range da entrada analógica é de `1` (total esquerda) até `32768` (total direita). 

```py
# total esquerda
j.set_axis(pyvjoy.HID_USAGE_X, 0x1)

# total direita
j.set_axis(pyvjoy.HID_USAGE_X, 32768)
```

## pyautogui

O pyautogui é um lib que permite emularmos ações do teclado e mouse via python.

### Manter tecla pressionada

Por padrão a lib não permite manter uma tecla pressionada (e ficar repetitivamente enviando o mesmo valor), para desativar basta remover o delay:

```py
    def __init__(self, port, baudrate):
        pyautogui.PAUSE = 0  ## remove delay
```

Agora uma tecla "pressionada" ira ser enviada repetitivamente

### keyboard

- https://pyautogui.readthedocs.io/en/latest/keyboard.html#

O pyautogui disponibiliza duas formas diferentes de apertarmos uma tecla: 

- `press` que é uma ação de apertar e soltar uma tecla
- `keyDown` e `keyUp` que são aćoes distintas de apertar e soltar

```py
pyautogui.keyDown('shift')  # hold down the shift key
pyautogui.press('left')     # press the left arrow key
pyautogui.press('left')     # press the left arrow key
pyautogui.press('left')     # press the left arrow key
pyautogui.keyUp('shift')    # release the shift key
```

Para uma lista des teclas suportas acesse:

- https://pyautogui.readthedocs.io/en/latest/keyboard.html#keyboard-keys

Se precisar fazer um combo (hotkeys) de teclas como o: `ctrl` + `alt` + `f4`, use o `hotkeys`:

```py
pyautogui.hotkey('ctrl', 'shift', 'f4')
```

### Emulando mouse

A documentacão oficial é muito boa:

- https://pyautogui.readthedocs.io/en/latest/mouse.html

