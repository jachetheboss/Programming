// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

/* '''Python 
x = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41
# to
print( x )
print(len(str(x))) -- prints 15, prod of primes from 2 to 41 is ~3*10^14, just 13 primes 

can probably just to top-down recursive gradient descent, for every square, find the quotient 
10^14 / square = quo, then find the number of single-copy-factor numbers <= quo? By single copy,
means prime factorization has only 1 copy of each prime factor, squareless number.
*/

const BOUND : number = 100000000000000; // 10^14 can fit within number, don't need bigint 
let root_bound : number = Math.floor(Math.sqrt(BOUND));
let squares : number[] = [];
for(let root : number = 1; root <= root_bound; root++){
	squares.push(root * root);
}