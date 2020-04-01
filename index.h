const char MAIN_page[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width,initial-scale=1.0">
<html>
<!-- HTML_STYLE -->
<style>
    body {
        text-align: center;
        font-family: helvetica;
        background-color: lightskyblue;
    }

    form {
        display: flex;
    }

    .container {
        background-color: whitesmoke;
        display: flex;
        flex-direction: column;
        justify-content: center;
        border: solid 1px lightgray;
        border-radius: 5px;
        width: 500px;
        margin: auto;
    }

    .column {
        display: flex;
        flex-direction: column;
        width: 100%;
    }

    .setting-container {
        display: flex;
        flex-direction: column;
        border-bottom: 1px solid lightgray;
    }
    .setting-container form {
        flex-wrap: wrap;
        justify-content: flex-end;
        padding: 10px;
    }
    .setting-container label {
        display: flex;
        align-items: center;
        justify-content: flex-start;
        width: 19%;
        margin: 5px 0 5px;
    }
    .setting-container input[type='text'], input[type='checkbox'] {
        width: 79%;
        margin: 5px 0 5px;
        height: 30px;
        border: none;
        border-radius: 5px;
    }
    #file-update-label {
        background-color: white;
        border-radius: 5px;
        padding: 5px;
        height: 30px;
        margin: auto;
        width: 70%;
    }
    .row {
        display: flex;
        flex-direction: row;
        align-items: center;
        justify-content: space-between;
        flex-wrap: wrap;
    }

    .hidden {
        display: none !important;
    }

    #top-bar {
        display: flex;
        flex-direction: row;
        justify-content: flex-end;
        flex-wrap: wrap;
        border-bottom: solid 1px lightgray;
    }

    .row>.label {
        margin-left: 10px;
    }

    .set {
        display: flex;
        flex-direction: column;
        width: 100%;
        background-color: lightgray;
        padding: 10px;
    }

    .set>.set-inputs {
        display: flex;
        flex-direction: column;
    }

    .set>.set-inputs input {
        width: 80%;
        height: 30px;
        border: none;
        border-radius: 5px;
        padding-left: 10px;
        margin-top: 5px;
        margin-bottom: 5px;
    }

    select {
        width: 50%;
        height: 30px;
        border: none;
        margin-top: 5px;
        margin-bottom: 5px;
    }

    .set>.set-buttons {
        display: flex;
        flex-direction: row;
        justify-content: flex-end;
    }

    .btn-container {
        display: flex;
    }

    .btn {
        border-radius: 5px;
        padding: 15px 32px;
        text-align: center;
        transition-duration: 0.4s;
        margin: 10px 5px;
        cursor: pointer;
        text-decoration: none;
    }

    .edit {
        background-color: dodgerblue;
        border: solid 1px dodgerblue;
        color: white;
    }

    .edit:hover {
        color: dodgerblue;
    }

    .on,
    .save {
        background-color: yellowgreen;
        border: solid 1px yellowgreen;
        color: white;
    }

    .on:hover,
    .save:hover {
        color: yellowgreen;
    }

    .off,
    .delete {
        background-color: tomato;
        border: solid 1px tomato;
        color: white;
    }

    .off:hover, .delete:hover {
        color: tomato;
    }

    .cancel {
        background-color: lightgray;
        border: solid 1px lightgray;
        color: white;
    }

    .cancel:hover {
        color: lightgray;
    }

    .btn:hover {
        background-color: white;
    }

    .input-mode {
        pointer-events: none;
        background-color: white;
    }

    .input-mode.on {
        color: yellowgreen;
    }

    .input-mode.off {
        color: tomato;
    }
    #blocker {
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        top: 0;
        left: 0;
        z-index: 1;
        position: fixed;
        height: 100%;
        width: 100%;
        background: lightgray;
        opacity: 0.95;
        color: white;
    }
    .spinner {
        height: 30px;
        border-radius: 5px;
        background-color: lightgray;
    }
    .lds-ring {
        display: inline-block;
        position: relative;
        width: 80px;
        height: 80px;
    }
    .lds-ring div {
        box-sizing: border-box;
        display: block;
        position: absolute;
        width: 64px;
        height: 64px;
        margin: 8px;
        border: 8px solid #fff;
        border-radius: 50%;
        animation: lds-ring 1.2s cubic-bezier(0.5, 0, 0.5, 1) infinite;
        border-color: #fff transparent transparent transparent;
    }
    .lds-ring div:nth-child(1) {
        animation-delay: -0.45s;
    }
    .lds-ring div:nth-child(2) {
        animation-delay: -0.3s;
    }
    .lds-ring div:nth-child(3) {
        animation-delay: -0.15s;
    }
    @keyframes lds-ring {
        0% {
            transform: rotate(0deg);
        }
        100% {
            transform: rotate(360deg);
        }
    }
    @media only screen and (max-width: 600px) {
        body {
            margin: 0;
        }
        .container {
            width: 100%;
            border: none;
            border-radius: 0px;
        }
        .row {
            border-bottom: 1px solid lightgray
        }
        .stick {
            top: 0px;
            position: fixed;
            width: 100%;
            background-color: whitesmoke;
        }
    }
</style>
<!-- HTML_DOM -->
<body>
    <h1 id='title'>Controls</h1>
    <div class="lds-ring" id='page-loader'><div></div><div></div><div></div><div></div></div>
    <div class='container'>
        <div id='top-bar'>
            <a id='go-to-settings' onclick='switchPage()' class='btn edit'>settings</a>
            <a id='add-gpio' onclick='addGpio()' class='btn edit'>+</a>
            <a id='back' onclick='switchPage()' class='btn edit hidden'>back</a>
        </div>
        <div id='gpios' class='column'>
            
        </div>
        <div id='settings' class='column hidden'>
            <div id='update' class='setting-container'>
                <p>Software update</p>
                <form onsubmit='submitUpdate(event)' enctype='multipart/form-data' id='upload-form'>
                    <label for='file' id='file-update-label'>Choose file</label>
                    <input type='file' name='update' id='file' onchange='fillUpdateInput(this)' style=display:none>
                    <input id='submit-update-file' type='submit' class='btn save' value='Update'>
                </form>
            </div>
            <div id='mqtt' class='setting-container'>
                <p>MQTT</p>
                <form onsubmit='submitMqtt(event)' id='mqtt-form'>
                    <label for='pin'>Host:</label>
                    <input type='text' name='host' id='mqtt-host'>
                    <label for='pin'>Port:</label>
                    <input type='text' name='port' id='mqtt-port'>
                    <label for='pin'>User:</label>
                    <input type='text' name='user' id='mqtt-user'>
                    <label for='pin'>Password:</label>
                    <input type='text' name='password' id='mqtt-password'>
                    <label for='pin'>Topic:</label>
                    <input type='text' name='topic' id='mqtt-topic'>
                    <input id='submit-mqtt-pref' type='submit'class='btn save' value='Save'>
                </form>
            </div>
            <div id='telegram' class='setting-container'>
                <p>Telegram</p>
                <form onsubmit='submitTelegram(event)' id='telegram-form'>
                    <label for='name'>Active:</label>
                    <input type='checkbox' name='active' id='telegram-active'>
                    <label for='token'>Token:</label>
                    <input type='text' name='token' id='telegram-token'>
                    <input id='submit-telegram-pref' type='submit'class='btn save' value='Save'>
                </form>
            </div>
        </div>
    </div>
    <div id='blocker' class='hidden'>
        <h2 id='blocker-title'>Loading</h2>
        <div class="lds-ring"><div></div><div></div><div></div><div></div></div>
    </div>
</body>

</html>
<!-- HTML_SCRIPT -->
<script>
    var settings = {}
    var gpios = []
    var availableGpios = []
    var isSettingsMenuActivated = false
    const topBar = document.getElementById('top-bar')
    const stickHightTrigger = topBar.offsetTop

    const switchPage = () => {
        isSettingsMenuActivated = !isSettingsMenuActivated
        const title = document.getElementById('title')
        title.innerText = isSettingsMenuActivated ? 'Settings' : 'Controls'
        if (isSettingsMenuActivated) {
            document.getElementById('go-to-settings').classList.add('hidden')
            document.getElementById('add-gpio').classList.add('hidden')
            document.getElementById('gpios').classList.add('hidden')
            document.getElementById('back').classList.remove('hidden')
            document.getElementById('settings').classList.remove('hidden')
        } else {
            document.getElementById('go-to-settings').classList.remove('hidden')
            document.getElementById('add-gpio').classList.remove('hidden')
            document.getElementById('gpios').classList.remove('hidden')
            document.getElementById('back').classList.add('hidden')
            document.getElementById('settings').classList.add('hidden')
        }
    }

    const fillUpdateInput = (element) => {
        const fileName = element.value.split('\\\\');
        document.getElementById('file-update-label').innerHTML = fileName[fileName.length-1];
    }

    const submitUpdate = async (e) => {
        e.preventDefault();
        const blocker = document.getElementById('blocker')
        blocker.classList.remove('hidden')
        document.getElementById('blocker-title').innerText = 'Loading new software, please wait...'
        const form = document.getElementById('upload-form')
        const data = new FormData(form);
        try {
            const res = await fetch(window.location.href + 'install', {
                method: 'POST',
                headers: { contentType: false, processData:false },
                body: data
            })
            blocker.classList.add('hidden')
            location.reload()
        } catch (err) {
            blocker.classList.add('hidden')
            console.error(`Error: ${err}`);
        }
    }

    const submitTelegram = async (e) => {
        e.preventDefault()
        const active = +document.getElementById(`telegram-active`).checked
        const token = document.getElementById(`telegram-token`).value
        if (token != settings.telegram.token || active != settings.telegram.active) {
            try {
                const res = await fetch(window.location.href + 'telegram', {
                    method: 'POST',
                    headers: { contentType: false, processData:false },
                    body: JSON.stringify({token, active})
                })
            } catch (err) {
                console.error(`Error: ${err}`)
            }
        }
    }

    const submitMqtt = async (e) => {
        e.preventDefault()
        const host = document.getElementById(`mqtt-host`).value
        const port = document.getElementById(`mqtt-port`).value
        const user = document.getElementById(`mqtt-user`).value
        const password = document.getElementById(`mqtt-password`).value
        const topic = document.getElementById(`mqtt-topic`).value
        try {
            const res = await fetch(window.location.href + 'mqtt', {
                method: 'POST',
                headers: { contentType: false, processData:false },
                body: {host, port, user, password, topic}
            })
        } catch (err) {
            console.error(`Error: ${err}`)
        }
    }

    const fetchGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios');
            const newGpios = await res.json()
            if (newGpios && newGpios.length) {
                gpios = newGpios
            }
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const fetchSettings = async () => {
        try {
            const res = await fetch(window.location.href + 'settings');
            const s = await res.json()
            if (s) {
                settings = s
                document.getElementById(`telegram-active`).checked = settings.telegram.active
                document.getElementById(`telegram-token`).value = settings.telegram.token
                document.getElementById(`mqtt-host`).value = settings.mqtt.host
                document.getElementById(`mqtt-port`).value = settings.mqtt.port
                document.getElementById(`mqtt-user`).value = settings.mqtt.user
                document.getElementById(`mqtt-password`).value = settings.mqtt.password
                document.getElementById(`mqtt-topic`).value = settings.mqtt.topic
            }
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const fetchAvailableGpios = async () => {
        try {
            const res = await fetch(window.location.href + 'gpios/available');
            availableGpios = await res.json()
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const switchState = async (element) => {
        try {
            const isOn = element.classList.value.includes('on')
            await fetch(`${window.location.href}digital/${element.id.split('-')[1]}/${isOn ? 0 : 1}`);
            element.classList.remove(isOn ? 'on' : 'off')
            element.classList.add(isOn ? 'off' : 'on')
            element.innerText = (isOn ? 'off' : 'on')
        } catch (err) {
            console.error(`Error: ${err}`);
        }
    }

    const openSetting = (element) => {
        closeSettings()
        const gpio = gpios.find(gpio => gpio.pin === +element.id.split('-')[1])
        const row = document.getElementById('row-' + gpio.pin)
        if (!row.classList.value.includes('open')) {
            row.appendChild(createEditElement(gpio))
            row.classList.add('open')
        }
    }

    const saveSetting = async (element) => {
        const gpioPin = element.id.split('-')[1]
        const isNew = gpioPin === 'new'
        let req = { settings: {} }
        const newPin = document.getElementById(`setPin-${gpioPin}`).value
        const newLabel = document.getElementById(`setInputLabel-${gpioPin}`).value
        const newMode = document.getElementById(`setMode-${gpioPin}`).value
        if (newPin && newPin != gpioPin) {
            req.settings.pin = +newPin
        }
        if (newLabel) {
            req.settings.label = newLabel
        }
        if (newMode) {
            req.settings.mode = newMode
        }
        if (!isNew) {
            req.pin = gpioPin
        }
        try {
            const resp = await fetch(`${window.location.href}gpio${isNew ? '/new' : ''}`, {
                method: 'POST',
                headers: {
                    'Accept': 'application/json',
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(req)
            });
            const newSetting = await resp.json()
            let column = document.getElementById('gpios')
            if (isNew) {
                gpios.push(newSetting.settings)
                column.insertBefore(createGpioElement(newSetting.settings), column.firstChild)
                closeSettings()
            } else {
                gpios = gpios.map(oldGpio => {
                    if (oldGpio.pin == +gpioPin) {
                        return { 'pin': newSetting.pin, 'label': newSetting.label, 'mode': newSetting.mode, 'state': newSetting.state }
                    }
                    return oldGpio
                })
                let oldRow = document.getElementById('row-' + gpioPin)
                column.replaceChild(createGpioElement(newSetting), oldRow)
            }
        } catch (err) {
            console.error(err)
        }
    }

    const deleteGpio = async (element) => {
        const gpioPin = element.id.split('-')[1]
        try {
            await fetch(`${window.location.href}gpio/${gpioPin}/delete`);
            await fetchGpios()
            let row = document.getElementById('row-' + gpioPin)
            closeSettings()
            let column = document.getElementById('gpios')
            column.removeChild(row)
        } catch (err) {
            console.error(err)
        }
    }

    const closeSettings = () => {
        document.querySelectorAll('.open').forEach(row => {
            row.classList.remove('open')
            row.removeChild(row.lastChild)
        })
    }

    const addGpio = () => {
        closeSettings()
        const topBar = document.getElementById('top-bar')
        if (!topBar.classList.value.includes('open')) {
            topBar.appendChild(createEditElement())
            topBar.classList.add('open')
        }
    }

    const updateModeOptions = (pin) => {
        const selectPin = document.getElementById(`setPin-${pin || 'new'}`)
        const selectMode = document.getElementById(`setMode-${pin || 'new'}`)

        const availableGpioInfos = availableGpios.find(gpio => gpio.pin == selectPin.value)
        if (availableGpioInfos.inputOnly && selectMode.childElementCount === 3) {
            selectMode.removeChild(selectMode.lastChild)
        } else if (!availableGpioInfos.inputOnly && selectMode.childElementCount === 2) {
            let option = document.createElement('div')
            option.innerHTML = `<option value=2>OUTPUT</option>`
            selectMode.appendChild(option.firstChild)
        }
    }
    // Element creation

    const createGpioElement = (gpio) => {
        let child = document.createElement('div');
        child.innerHTML = `<div class='row' id='row-${gpio.pin}'>
            <div class='label'> ${gpio.label}</div>
            <div class='btn-container'>
                <a onclick='openSetting(this)' id='edit-${gpio.pin}' class='btn edit'>edit</a>
                <a onclick='switchState(this)' id='state-${gpio.pin}' class='btn ${gpio.state ? 'on' : 'off'} ${gpio.mode != 2 ? 'input-mode' : ''}'>${gpio.state ? 'on' : 'off'}</a>
            </div>
        </div>`
        return child.firstChild;
    }

    const createEditElement = (gpio) => {
        if (!gpio) {
            gpio = {
                pin: 'new',
                label: 'Label will be displayed on the lcd screen'
            }
        }
        let modeOptions = `<option ${gpio.mode == 1 ? 'selected' : ''} value=1>INPUT</option><option ${gpio.mode == 5 ? 'selected' : ''} value=5>INPUT_PULLUP</option>`
        const pinOptions = availableGpios.reduce((prev, availableGpio) => {
            if ((!gpios.find(_gpio => _gpio.pin == availableGpio.pin) && availableGpio.pin != gpio.pin) || availableGpio.pin == gpio.pin) {
                // Complete the mode select input while we are here...
                if (availableGpio.pin == gpio.pin && !availableGpio.inputOnly) {
                    modeOptions += `<option ${gpio.mode == 2 ? 'selected' : ''} value=2>OUTPUT</option>`
                }
                prev += `<option ${availableGpio.pin == gpio.pin ? 'selected' : ''} value=${availableGpio.pin}>${availableGpio.pin}</option>`
            }
            return prev
        },[])
        let child = document.createElement('div')
        child.classList.add('set')
        child.innerHTML = `<div class='set-inputs'>
                <div class='row'>
                    <label for='pin'>pin:</label>
                    <select id='setPin-${gpio.pin}' name='pin' onchange='updateModeOptions("${gpio.pin}")'>${pinOptions}</select>
                </div>
                <div class='row'>
                    <label for='label'>label:</label>
                    <input id='setInputLabel-${gpio.pin}' type='text' name='label' placeholder='${gpio.label}'>
                </div>
                <div class='row'>
                    <label for='mode'>input mode:</label>
                    <select id='setMode-${gpio.pin}' name='mode'>${modeOptions}</select>
                </div>
                </div>
            <div class='set-buttons'>
                <a onclick='closeSettings()' id='cancel-${gpio.pin}' class='btn cancel'>cancel</a>
                ${gpio.pin === "new" ? '' : `<a onclick='deleteGpio(this)' id='delete-${gpio.pin}' class='btn delete'>delete</a>`}
                <a onclick='saveSetting(this)' id='save-${gpio.pin}' class='btn save'>save</a>
            </div>`
        return child
    }

    const createSpinner = () => {
        let spinner = document.createElement('div')
        spinner.classList.add('spinner')
        spinner.innerHTML = '<div class="lds-ring"><div></div><div></div><div></div><div></div></div>'
        return spinner
    }

    window.onload = async () => {
        await fetchGpios()
        await fetchAvailableGpios()
        const container = document.getElementById('gpios')
        gpios.forEach(gpio => {
            container.appendChild(createGpioElement(gpio))
        })
        await fetchSettings()
        document.getElementById('page-loader').remove()
    };

    window.onscroll = () => {
        if (window.pageYOffset > stickHightTrigger) {
            topBar.classList.add("stick")
        } else {
            topBar.classList.remove("stick")
        }
    };
</script>
)=====";