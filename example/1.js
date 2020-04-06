const { XpathWrapper } = require('../');

const xml = `
<root>
    hello
</root>
`

const wrapper = new XpathWrapper(xml, '/root');

const data = wrapper.getData(0, '.');

console.log(data);