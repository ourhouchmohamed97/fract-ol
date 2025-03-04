import figlet from 'figlet';
import chalk from 'chalk';

// Add space between each character
const text = 'F r a c t o l';

// Generate ASCII text with spaces
figlet.text(text, { font: 'Big' }, function (err, data) {
    if (err) {
        console.log('Something went wrong...');
        console.dir(err);
        return;
    }

    // Add color using Chalk
    console.log(chalk.cyan.bold(data)); // Change 'cyan' to any color you like
});


