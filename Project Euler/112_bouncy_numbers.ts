// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

// single run attempt 
// use backtracking to keep finding the number of non-increasing elements, if it's a palindrome
// (1111111111 or 22222222 ...... 99999999) then don't multiply by 2

const MAX_LEN : number = 10;
const THRES : number = 0.99;
const BRUTE_MAX_LEN : number = 7;

function isBouncy(num : number) : boolean {
	let increasing : number = 0;
	// increasing is the current state, 1 means increasing, 0 means undetermined,
	// -1 means decreasing
	let prev_d : number = -1;
	while(num > 0){
		let d : number = num % 10;
		if(prev_d === -1){
			prev_d = d;
			num = Math.floor(num / 10);
			continue;
		}
		if(increasing === 0){
			if(d < prev_d) increasing = 1;
			else if(d > prev_d) increasing = -1;
		}
		else if(increasing === 1 && d > prev_d) return true;
		else if(increasing === -1 && d < prev_d) return true;

		prev_d = d;
		num = Math.floor(num / 10);
	}
	return false;
}

// not sure if the bouncy number ratio is monotonically increasing

function isPalindrome(arr : number[]) : boolean { // only taking in non-decreasing arrays,
// so don't have to check all indices in the array
	return arr[0] === arr[arr.length - 1];
}

let good_counts : number[] = [0];
for(let len : number = 1; len <= MAX_LEN; len++){
	let good_count : number = 0;
	let combo : number[] = Array<number>(len);
	for(let i : number = 0; i < combo.length; i++) combo[i] = 1;
	while(combo.length > 0){
		if(isPalindrome(combo)) good_count++;
		else good_count += 2;
		while(combo.length > 0 && combo[combo.length - 1] === 9) combo.pop();
		if(combo.length === 0) break;
		combo[combo.length - 1]++;
		while(combo.length < len) combo.push(combo[combo.length - 1]);
	}
	good_counts.push(good_count);
}
let prefix : number[] = [good_counts[0]];
for(let i : number = 1; i < good_counts.length; i++){
	prefix.push(prefix[prefix.length - 1] + good_counts[i]);
}

let suffice_len : number = -1;
for(let i : number = 0; i < prefix.length; i++){
	let bouncy_ratio : number = 1.0 - (1.0 * prefix[i] / (10**i - 1));
	if(bouncy_ratio > THRES){
		suffice_len = i;
		console.log("len", suffice_len, "should suffice");
		break;
	}
}

if(suffice_len <= BRUTE_MAX_LEN){
	// can try to brute force now, 10^7 should be quick but 10^8 might be a lil slow
	let bouncy_count : number = 0;
	let x : number = 1;
	let mx : number = 10**BRUTE_MAX_LEN;
	let ans : number = -1;
	while(x <= mx){
		if(isBouncy(x)) bouncy_count++;
		if(x % (x - bouncy_count) === 0 && (x - bouncy_count) * 100 === x){
			ans = x;
			break;
		}
		x++;
	}
	console.log("ans:", ans);
}else{
	console.log("suffice len is > 7, might need to explore options faster than brute force,\
		maybe using counting DP (keeping track of count rather than generating every non-\
		bouncy number");
}
