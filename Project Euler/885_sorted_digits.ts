// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

let start_t : number = performance.now();

const MAX_LEN : number = 18;
const MOD : bigint = 1123455689n;
const TEN : bigint = 10n;

// generate them all using DP,
// then generate them all using backtracking (saves a fuckton of memory!)
let big_digits : bigint[] = [];
for(let d : number = 0; d < 10; d++) big_digits.push(BigInt(d));

let DP : bigint[][][] = [];
for(let i : number = 0; i < MAX_LEN + 1; i++){
	let arr : bigint[][] = [];
	for(let j : number = 0; j < 10; j++) arr.push( [] );
	DP.push(arr);
}
for(let j = 1; j < DP[1].length; j++) DP[1][j].push( big_digits[j] );
for(let i = 2; i < DP.length; i++){
	for(let d : number = 1; d < 10; d++){
		for(let prev_d : number = 1; prev_d <= d; prev_d++){
			for(let x of DP[i - 1][prev_d]){
				DP[i][d].push(x * TEN + big_digits[d]);
			}
		}
	}
}
// console.log("DP:", DP);

// precompute factorials for quick reference later
let factorial : bigint[] = [BigInt(1)];
for(let i : number = 1; i <= MAX_LEN; i++){
	factorial.push(factorial[factorial.length - 1] * BigInt(i));
}
console.log("factorial:", factorial);

let ans : bigint = 0n;

let counter : number = 0;

let s : string = "";
for(let i : number = 0; i < MAX_LEN; i++) s += "1";
let pattern : bigint = BigInt(s);

for(let len : number = 1; len < DP.length; len++){ // len is length of sorted digits after discarding zeros
	for(let arr of DP[len]){
		for(let x of arr){
			// x is a bigint of sorted digits without zeros 
			let freq : number[] = Array<number>(10);
			for(let i : number = 0; i < 10; i++) freq[i] = 0;

			let ori_x : bigint = x;

			while(x > 0){
				let d = Number(x % TEN);
				freq[d]++;
				x /= TEN;
			}
			freq[0] = MAX_LEN - len;

			let ways : bigint = factorial[MAX_LEN];
			for(let count of freq){
				ways /= factorial[count];
			}
			// we're finding the sum of such numbers, not the number of such numbers
			// lmao I just found the sum of all numbers in their original form, I'm supposed 
			// to find the sum of numbers' form when sorted! FUCK!
			// let sum : bigint = 0n;
			// for(let d : number = 1; d < 10; d++){
			// 	let count : number = freq[d];
			// 	let total_occur : bigint = ways * BigInt(count) / BigInt(MAX_LEN);
			// 	let incr : bigint = total_occur * BigInt(d) * pattern;
			// 	sum += incr;
			// }
			// ans += sum;
			// ans %= MOD;

			ans += ori_x * ways;
			ans %= MOD;

			// if(counter < 100){
			// 	console.log("x:", ori_x);
			// 	console.log("freq:", freq);
			// 	console.log("sum:", sum);
			// 	counter++;
			// }
		}
	}
}
console.log("ans:", ans);

let finish_t : number = performance.now();
console.log("elapsed milliseconds:", finish_t - start_t);