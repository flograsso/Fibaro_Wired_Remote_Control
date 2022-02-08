# Fibaro_Wired_Remote_control

# HTTP

Los POST a hacer son los siguientes:

- Obtener info de la config del canal. Este comando nos da respuesta por el puerto serie

```
POST [IP_ADDRESS]/channelmode?CH=1 
```

- Enviar comando de PROG

```
POST [IP_ADDRESS]/programacion?CH=1 
```

- Enviar comando de ACCION

```
POST [IP_ADDRESS]/cortina?CH=1&ACTION=U
```

Donde las acciones pueden ser:
- D: DOWN (bajar)
- U: UP (subir)
- S: STOP (parar)
- F: FAVORITE (posicion favorita)

## Home Center

1. Importar el dispositivo virtual adjunto.
2. Cambiarle el icono.
3. Elegir la habitación, la IP que tendrá asignada el ESP32, el puerto (80), ponerle "blinds" en tipo. 
4. Configurar el CH del POST.

Para enviarlo desde el Home Center de Fibaro, se debe enviar el CRLF forzadamente. Por lo que es al request hay que sumarle este HEX:

```
0x0D0x0A0x0D0x0A
```
Y quedaría asi:
```
POST /cortina?CH=1&ACTION=U HTTP/1.10x0D0x0A0x0D0x0A
```