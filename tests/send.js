const axios = require('axios').default

axios.get('http://192.168.4.22:8080/getData?cod=ALM01234')
    .then(function (resp) {
        // handle success

        const objetct = resp.data

        console.log(resp.statusText);
        console.log(objetct);
    })