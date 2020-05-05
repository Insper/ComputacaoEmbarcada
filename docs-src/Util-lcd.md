# LCD max Touch

## Orientação

Podemos fazer o LCD ser orientando na vertical (portrait) ou horizontal (landscape), para isso, basta alterar a função `static void configure_lcd(void){...}`

=== "portrait"
    ```c
    static void configure_lcd(void){
      /* Initialize display parameter */
      g_ili9488_display_opt.ul_width = ILI9488_LCD_WIDTH;
      g_ili9488_display_opt.ul_height = ILI9488_LCD_HEIGHT;
      g_ili9488_display_opt.foreground_color = COLOR_CONVERT(COLOR_WHITE);
      g_ili9488_display_opt.background_color = COLOR_CONVERT(COLOR_WHITE);

      /* Initialize LCD */
      ili9488_init(&g_ili9488_display_opt);
    }
    ```
    
=== "landscape"
    ```c
    static void configure_lcd(void){
      /* Initialize display parameter */
      g_ili9488_display_opt.ul_width = ILI9488_LCD_WIDTH;
      g_ili9488_display_opt.ul_height = ILI9488_LCD_HEIGHT;
      g_ili9488_display_opt.foreground_color = COLOR_CONVERT(COLOR_WHITE);
      g_ili9488_display_opt.background_color = COLOR_CONVERT(COLOR_WHITE);

      /* Initialize LCD */
      ili9488_init(&g_ili9488_display_opt);
      ili9488_set_display_direction(PORTRAIT);
    }
    ```
    
    Alterar o arquivo `ili9488.h` os defines de `WIDTH` e `HEIGTH`:
    
    ```c
    /* ILI9488 screen size */
    #define ILI9488_LCD_WIDTH  480
    #define ILI9488_LCD_HEIGHT 320 
    ```
    
    Altere na `task_mxt` como o touch é gerencido:
    
    ```c
    if(first == 0 ){
        *x = ILI9488_LCD_WIDTH - ILI9488_LCD_WIDTH*touch_event.x/4096;
        *y = ILI9488_LCD_HEIGHT - ILI9488_LCD_HEIGHT*touch_event.y/4096;
        first = 1;
    }
    ```
    
!!! note
    Note que está trocado, quando queremos `landscape` chamamos por `PORTRAIT`, isso se dá por um erro em um `enumarete` fornecido pelo driver do LCD, no arquivo `ili9488.h`:
    
    ```c
    enum ili9488_display_direction{
	LANDSCAPE  = 0,
	PORTRAIT   = 1
    };
    ```
