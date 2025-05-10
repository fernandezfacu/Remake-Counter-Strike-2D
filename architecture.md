# Protocol

## Client

Puede enviar todos estos requests:

- Crear nombre de usuario

    0x01 <length-username> <username>
    
    siendo <length-username> un numero de dos bytes big endian

- Crear partida

    0x02 

- Unirse partida

    0x03 <length-match> <match-id>

    siendo <length-match> un numero de dos bytes big endian

- Comprar arma

    0x04 <weapon-code>

    siendo <weapon-code> un byte 

- Comprar balas

    0x05 <type-weapon> <count>

    siendo <type-weapon> un byte 

    0x01: arma primaria
    0x02: arma secundaria

    <count>: un numero big endian
- Rotar
- Moverse


- Disparar
- Apuntar?
- Cambiar arma
- Plantar la bomba
- Defusear la bomba

#

| Arma   | Código de arma |
|--------|----------------|
| none   | 0x00           |
| glock  | 0x01           |
| ak-47  | 0x02           |
| m3     | 0x03           |
| awp    | 0x04           |

## Server

Los mensajes que envia el server son

- Creaste exitosamente tu nombre de usuario
    0x01 0x01
- Creaste no existosamente tu nombre de usuario
    0x01 0x00
- Creaste exitosamente una partida
    0x02 0x01
- No creaste exitosamente una partida
    0x02 0x00
- Te uniste exitosamente a una partida
    0x03 0x01
- No te uniste exitosamente a una partida
    0x03 0x00
- Envio equipamiento
    0x04 <money> <knife> <primary-weapon-code> <primary-weapon-bullets> <secondary-weapon-code> <secondary-weapon-bullets>

    - <money>: numero dos bytes big endian
    - <knife>: 0x01 si lo tiene equipado, 0x00 si no (nunca debería pasar)
    - <primary-weapon-code>: un byte
    - <primary-weapon-bullets>: dos bytes big endian
    - <secondary-weapon-code>: un byte
    - <secondary-weapon-bullets>: dos bytes big endian

- Arranca la fase de compra?
- Arranca la ronda en sí
- Cambio de lado?
- Snapshot de la ronda en sí
