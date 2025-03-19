import figlet from 'figlet';
import chalk from 'chalk'; // Optional, only for coloring

// Clear console
console.clear();

// Generate ASCII text
figlet.text('FRACTOL', { font: 'Big' }, function (err, data) {
    if (err) {
        console.log('Something went wrong...');
        console.dir(err);
        return;
    }

    // Apply a solid color directly (cyan in this case)
    const solidColorText = chalk.cyan.bold(data);  // Change 'cyan' to any other color if needed

    // Display the solid color text
    console.log(solidColorText);
});

