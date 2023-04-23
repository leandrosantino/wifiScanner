const serialPort = require('./serialport')()

const data = {
    'ALM01234': {
        nome: 'sensor Sick de infravermelho 45897 de alta potencia de ceramica ',
        endereco: 'A1102',
        estoque:  1,
    },
    'ALM01235': {
        nome: 'Dijuntor tripolar Shimender',
        endereco: 'A1102',
        estoque:  1,
    }
}

const historico = []

const actions = {
    getData({code}){
        return toCode(data[code])
    },
    sendUpdate({code, estoque}){
        const item = data[code]
        const diff  = item.estoque-estoque
        const type = diff<0?'saída':'entrada' 
        historico.unshift(`${type} de ${Math.abs(diff)} no item ${item.nome}`)

        console.log(historico)

        return toCode({
            status: 'ok',
            message: 'updade successfull'
        })
    }
}


async function main(){
    const port = await serialPort.init()
    if(port){
        port.on('readable', ()=>{
            try{
                let msg = toJson(port.read().toString())
                console.log(msg)
                const {type, params} = msg
        
                const resp = actions[type](params)
                console.log(resp)
        
                port.write(resp)
            }catch(err){
                console.log('erro', err)
            }       
        })
        port.on('close', ()=>console.log('closed'))
    }else{
        console.log('device disconnected')
    }
}

main()

function toCode(object){

    let str = ''
    const keys = Object.keys(object)

    keys.forEach((_key, index)=>{
        const vrg = keys.length == index+1?'':';'
        let key = _key.toLocaleUpperCase().split('')
        key = `${key[0]}${key[1]}`
        str+=`${key}:${object[_key]}${vrg}`
    })

    return str
    
}


function toJson(srt = ''){
    const data = {
        type: '',
        params:{}
    }
    const keys = {
        c: 'code',
        e: 'estoque',
        GD: 'getData',
        SU: 'sendUpdate'

    }
    const params = srt.split(';')

    params.forEach(param=>{
        const val = param.split(':')

        if(val[0] == 't'){
            let resp = keys[val[1].replace('\r\n', '')]
            data.type = resp
        }else{
            let resp = val[1].replace('\r\n', '')
            if(val[0] == 'e'){resp = Number(resp)}
            data.params[keys[val[0]]] = resp
        }
    })
    return data
}

//tamanho máxino da string de recebimento : 32
//c:ALM01234;t:GT;e:1234
