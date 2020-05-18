# Float Print (Atmel Studio)

Configurações necessárias para executar o código `printf("%f",var)` na IDE Atmel Studio

1. Vá na janela `Solution Explorer` e clique com o botão direito no seu `Project Properties` e depois clique em `Properties`

   ![1](imgs/Util_FloatPrint/1.png)

   

1. Vá na aba `Toolchain` e clique na opção `Symbols` dentro de `ARM/GNU C Compiler`

   ![2](imgs/Util_FloatPrint/2.png)

   

1. Selecione o define `printf=iprintf` e clique na opção `Delete Item`

   ![3](imgs/Util_FloatPrint/3.png)

   

1. Basta compilar seu código novamente que o comando `printf("%f",var)` irá funcionar.

