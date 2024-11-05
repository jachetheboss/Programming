// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

// special bigint type
// do a lot of grouping, multiplying to save operations 

/* 1 - 8 special, a little bit of a stagger in the grouping

   1
   2
   3
...
   8
[  // 9, 19, 29, ... 89, similar to 10, 20, 30, ... 90
   9

  19
  29
...
  89
 ]
 [
  99

 199
 299
...
899
]
 999
 
1999
.......
*/
// bunch of 9s, 1-9 once 
// same as above, but 9 less 9s
/// etc. etc., until it is just 1-x, where 1 <= x <= 9
// boils down to 45 + 450 + 4500 + 45000 + ... + (1 + 2 + ... + x) * 10^y 
// find x = fib(n) % 9
// then the 99999... parts can be thought of as a power of 10 minus 1

// (1 + 1 + ... 1), 9 ones, (10 + 10 + .... 10), 9 10s, 9 100s, 9 1000s, etc.
// but have to decrement by 1 for every number up to whatever quintillion

// probably going to have to do some fast exponentiation shit

// this should be the global scope
const ZERO : bigint = 0n;
const ONE : bigint = 1n;
const TWO : bigint = 2n;
const FIVE : bigint = 5n;
const EIGHT : bigint = 8n;
const NINE : bigint = 9n;
const TEN : bigint = 10n;
const MOD : bigint = 1000000007n;
const FORTYFIVE : bigint = 45n;

function getBinaryString(n : bigint) : string { // n >= 1
	let bin : string = "";
	let pow2 : bigint = 1n;
	while(pow2 <= n){
		if((pow2 & n) === pow2) bin += '1';
		else bin += '0';
		//pow2 *= 2; // this 2 might have to be a bigint
		pow2 *= TWO;
	}
	// reverse string 
	let rev : string = "";
	for(let i = bin.length - 1; i >= 0; i--) rev += bin[i];
	
	bin = rev;
	return bin;
}
function S(n : bigint, MOD : bigint) : bigint {
	
	if(n <= EIGHT){
      let total : bigint = n * (n + ONE) / TWO; // should return a bigint type
    //   console.log("n:", n, "total:", total);
		return total;
	}
	
	// n guaranteed to be > 0, so at least one of quo and rem will be > 0
		
	let quo : bigint = (n - EIGHT) / NINE; // how many "groups" of nine
	//console.log("quo:", quo);
	let rem : bigint = (n - EIGHT) % NINE; // rem will be between 0 and 8, but sure we can still keep
	// it as bigint type
	let total : bigint = ZERO; // we will return total 
	
	// will decrement separately for the quo and rem
	
	if(quo >= ONE){
		// bin used as the pattern for square-and-multiply-esque algo
		// quo is the target term
		let bin : string = getBinaryString(quo);
		//let lead : bigint = // don't need the "lead" and "addend" concept anymore
		// let addend : bigint = 
		
		// a1 * (r^n - 1) / (r - 1), r = 10, a1 = 450
		// 50 * (r^n - 1)
		
		let sum : bigint = TEN;
		for(let i : number = 1; i < bin.length; i++){
			sum *= sum;
			if(bin[i] === '1') sum *= TEN; // square and multiply algo
			sum %= MOD;
		}
		
		let decr : bigint = ONE; // decrement perfect power of 10 to 999999...
		sum -= decr;
		if(sum < ZERO) sum += MOD;
		sum *= FIVE * TEN; // * 50
		sum %= MOD;
			
		decr = quo * NINE;
		decr %= MOD;
		sum -= decr;
		if(sum < ZERO) sum += MOD;
		
		sum += EIGHT * (EIGHT + ONE) / TWO;
		sum %= MOD;
		
		total += sum;
		total %= MOD;
	}
	if(rem > ZERO){
		let coeff : bigint = rem * (rem + ONE) / TWO;
		// 10^(quo + 1)
		
		let bin : string = getBinaryString(quo + ONE);
		
		let sum : bigint = TEN;
		for(let i : number = 1; i < bin.length; i++){
			sum *= sum;
			if(bin[i] === '1') sum *= TEN; // square and multiply algo
			sum %= MOD;
		}
		sum *= coeff;
		sum %= MOD;
		let decr : bigint = rem;
		sum -= decr;
		if(sum < ZERO) sum += MOD;
		
		if(quo === ZERO){
			sum += EIGHT * (EIGHT + ONE) / TWO;
			sum %= MOD;
		}

		total += sum;
		total %= MOD;
	}

//    console.log("n:", n, "total:", total)

	return total;
}

let seq : bigint[] = [ ZERO, ONE ];
let num_terms : number = 90;
while(seq.length < num_terms + 1){ // want to find fib(90)
	let next_term : bigint = seq[seq.length - 2] + seq[seq.length - 1];
	seq.push(next_term);
}
// seq contains Fibonacci numbers from Fib(0) to Fib(90) inclusive
// using bigint since Fib(90) might overflow 2^53 - 1 TS largest integer that 
// can be expressed with exact precision in IEEE floating point (double?) representation
// in C++, long long would be enough, but not enough for TS default number type
console.log( `Fib(${seq.length - 1}) = ${seq[seq.length - 1]}` );
console.log("num digits:", seq[seq.length - 1].toString().length);

// sanity check
console.log("S(20) =", S(BigInt(20), MOD));

let ans : bigint = ZERO;

for(let term : number = 2; term < seq.length; term++){ // term of Fibonacci sequence

	ans += S(seq[term], MOD);
	ans %= MOD;
}

console.log("ans:", ans);

