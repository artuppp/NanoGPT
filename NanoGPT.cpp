#include <stdio.h>
#include "pico/stdlib.h"

#include "tensorflow/lite/core/c/common.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_profiler.h"
#include "tensorflow/lite/micro/recording_micro_interpreter.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/schema/schema_generated.h"

// Definimos un tamaño de memoria para TFLite (aunque en este test simple no llenaremos todo)
const int kTensorArenaSize = 2048;
uint8_t tensor_arena[kTensorArenaSize];

int main()
{
    // 1. Inicializar la salida estándar (UART o USB)
    stdio_init_all();
    
    // Opcional: Inicializar target específico de TFLM (útil para logs de debug en Pico)
    tflite::InitializeTarget();

    while (true) {
        sleep_ms(5000);

        printf("=========================================\n");
        printf("Test simple de TFLite Micro en Pico\n");

        // 2. PRUEBA 1: Verificar versión de la librería
        // Si esto imprime un número, los headers están bien.
        printf("1. Version Schema TFLite: %d\n", TFLITE_SCHEMA_VERSION);

        // 3. PRUEBA 2: Instanciar el Resolver
        // Esto prueba que el linker de C++ está encontrando la librería compilada (.a)
        // Reservamos espacio para 1 operación (ej. FullyConnected)
        static tflite::MicroMutableOpResolver<1> resolver;
        
        // Intentamos agregar una operación dummy para ver si la librería responde
        TfLiteStatus add_status = resolver.AddFullyConnected();
        
        if (add_status == kTfLiteOk) {
            printf("2. MicroMutableOpResolver: OK (Operacion agregada)\n");
        } else {
            printf("2. MicroMutableOpResolver: FALLO\n");
        }

        // 4. Conclusión
        printf(">>> Si lees esto, TFLM funciona correctamente.\n");
        printf("=========================================\n");

        sleep_ms(2000);
    }
}
