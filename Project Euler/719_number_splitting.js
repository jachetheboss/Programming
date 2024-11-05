// import "./performance.js";


"use strict";
"esversion: 11"
// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.
// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript
function declareArray(len, init_val) {
    let arr = [];
    for (let i = 0; i < len; i++)
        arr.push(init_val);
    return arr;
}
function incrementBuilder(builder) {
    for (let i = builder.length - 1; i >= 0; i--) {
        if (builder[i] === 0) {
            builder[i]++;
            return;
        }
        builder[i] = 0;
    }
}

function getDigits(num){
    let digits = [];
    while(num > 0){
        digits.push(num % 10);
        num = Math.floor(num / 10);
    }
    let rev = [];
    for(let i = digits.length - 1; i >= 0; i--) rev.push(digits[i]);
    return rev;
}

function check(digits, starts, target) {
    if(starts.length === 2) return false;
    
    let sum = 0;
    for (let i = 1; i < starts.length; i++) { // L is substring len
        let pow10 = 1;
        for(let j = starts[i] - 1; j >= starts[i - 1]; j--){ // this method of extracting digits, then
        // using base 10 mult/add is more than 5x faster than the method of creating all substrings
        // then parseing them to ints using parseInt func, allocating too much memory, too slow
            sum += pow10 * digits[j];
            if(sum > target) return false; // pruning optimization, early return
            pow10 *= 10;
        }
    }
    return sum === target;
}

let start_t = performance.now();

let pairs = [];
let n = 1000000;
//let n = 100;
let max_len = (n**2).toString().length;
for (let i = 4; i <= n; i++) { // don't want 1, 4, 9 since can't break them down to at least 2 numbers
    let square = i * i;
    pairs.push([i, square]);
}
let patterns = [];

let special = [];

for (let len = 0; len <= max_len; len++) {
    if (len < 2) {
        patterns.push([]);
        continue;
    }
    
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    // len >= 2 at this point
    let builder = declareArray(len, 0);
    builder[0] = 1; // 1 means begin a new substring, 0 means continue with current substring
    let ways = 2 ** (len - 1); // Python-esque exponentiation operator 
    let cand = [];
    // x-digit number where x is odd, sqrt root has x / 2 + 1 digits 
    // if x is even, then sqrt has x / 2 digits
    for (let way = 0; way < ways; way++) {
        let starts = [];
        for (let i = 0; i < builder.length; i++) {
            if (builder[i] === 1)
                starts.push(i);
        }
        starts.push(builder.length);
        // find max substring len 
        let max_sub_len = 0;
        for (let i = 1; i < starts.length; i++) { // L is substring len
            let L = starts[i] - starts[i - 1];
            if (L > max_sub_len) max_sub_len = L;
        }
        
        if (max_sub_len >= target_len - 2) {
            // if(max_sub_len === target_len - 2) special.push(starts);
            
            cand.push(starts);
        }
        incrementBuilder(builder);
    }
    patterns.push(cand);
}
// console.log("patterns:", patterns);
console.log("patterns.length", patterns.length);

let count = 0;

let sols = [];

let ans = 0n; // actually don't need bigint, since 
for (let pair of pairs) {
    let num = pair[0];
    let square = pair[1];
    //let s = square.toString();
    let digits = getDigits(square);
    // let len = s.length;
    let len = digits.length;
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    for (let starts of patterns[len]) {
        let ok = check(digits, starts, num);
        if(ok){
            ans += BigInt(square);
            count++;
            
            let max_sub_len = 0;
            for(let i = 1; i < starts.length; i++){
                if(starts[i] - starts[i - 1] > max_sub_len) max_sub_len = starts[i] - starts[i - 1];
            }
            if(max_sub_len === target_len - 2){
                special.push(num);
            }
            
            sols.push(square);
            
            if(count < 50){
                console.log("num:", num);
                console.log("square:", square);
                console.log(starts);
                console.log();
            }
            
            break;
        }
    }
}
console.log("ans:", ans);
console.log("count:", count);

let end_t = performance.now();

console.log("split candidates count:");
for(let cand of patterns){
    console.log(cand.length);
}

console.log("sols:");
for(let i = 0; i < sols.length; i += 100){
    console.log(sols.slice(i, i + 100));
}

let ans2 = 0;
for(let x of sols) ans2 += x;

console.log("ans2:", ans2);

console.log("special:", special)

console.log(`${end_t - start_t} milliseconds elapsed`);






/////// BELOW IS DEMONSTRATION OF HORRIBLE HEISENBUG, TOUGH TO FIND DUE TO ASSUMPTION OF INTEGER DIVISION,
/////// WHEN IT IS FLOAT DIVISION IN REALITY!
/*
// import "./performance.js";


"use strict";
"esversion: 11"
// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.
// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript
function declareArray(len, init_val) {
    let arr = [];
    for (let i = 0; i < len; i++)
        arr.push(init_val);
    return arr;
}
function incrementBuilder(builder) {
    for (let i = builder.length - 1; i >= 0; i--) {
        if (builder[i] === 0) {
            builder[i]++;
            return;
        }
        builder[i] = 0;
    }
}

function getDigits(num){
    let digits = [];
    while(num > 0){
        digits.push(num % 10);
        num = Math.floor(num / 10);
    }
    let rev = [];
    for(let i = digits.length - 1; i >= 0; i--) rev.push(digits[i]);
    return rev;
}

function check(digits, starts, target) {
    if(starts.length === 2) return false;
    
    let sum = 0;
    for (let i = 1; i < starts.length; i++) { // L is substring len
        let pow10 = 1;
        for(let j = starts[i] - 1; j >= starts[i - 1]; j--){ // this method of extracting digits, then
        // using base 10 mult/add is more than 5x faster than the method of creating all substrings
        // then parseing them to ints using parseInt func, allocating too much memory, too slow
            sum += pow10 * digits[j];
            if(sum > target) return false; // pruning optimization, early return
            pow10 *= 10;
        }
    }
    return sum === target;
}

let start_t = performance.now();

let pairs = [];
let n = 1000000;
//let n = 100;
let max_len = (n**2).toString().length;
for (let i = 4; i <= n; i++) { // don't want 1, 4, 9 since can't break them down to at least 2 numbers
    let square = i * i;
    pairs.push([i, square]);
}
let patterns = [];

let special = [];

for (let len = 0; len <= max_len; len++) {
    if (len < 2) {
        patterns.push([]);
        continue;
    }
    
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    // len >= 2 at this point
    let builder = declareArray(len, 0);
    builder[0] = 1; // 1 means begin a new substring, 0 means continue with current substring
    let ways = 2 ** (len - 1); // Python-esque exponentiation operator 
    let cand = [];
    // x-digit number where x is odd, sqrt root has x / 2 + 1 digits 
    // if x is even, then sqrt has x / 2 digits
    for (let way = 0; way < ways; way++) {
        let starts = [];
        for (let i = 0; i < builder.length; i++) {
            if (builder[i] === 1)
                starts.push(i);
        }
        starts.push(builder.length);
        // find max substring len 
        let max_sub_len = 0;
        for (let i = 1; i < starts.length; i++) { // L is substring len
            let L = starts[i] - starts[i - 1];
            if (L > max_sub_len) max_sub_len = L;
        }
        
        if (max_sub_len >= target_len - 1) {
            // if(max_sub_len === target_len - 2) special.push(starts);
            
            cand.push(starts);
        }
        incrementBuilder(builder);
    }
    patterns.push(cand);
}
// console.log("patterns:", patterns);
console.log("patterns.length", patterns.length);

let count = 0;

let sols = [];

let ans = 0n; // actually don't need bigint, since 
for (let pair of pairs) {
    let num = pair[0];
    let square = pair[1];
    //let s = square.toString();
    let digits = getDigits(square);
    // let len = s.length;
    let len = digits.length;
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    for (let starts of patterns[len]) {
        let ok = check(digits, starts, num);
        if(ok){
            ans += BigInt(square);
            count++;
            
            let max_sub_len = 0;
            for(let i = 1; i < starts.length; i++){
                let L = starts[i] - starts[i - 1];
                if(L > max_sub_len) max_sub_len = L;
            }
            if(max_sub_len === target_len - 2){
                special.push(num);
            }
            
            sols.push(square);
            
            if(count < 50){
                console.log("num:", num);
                console.log("square:", square);
                console.log(starts);
                console.log();
            }
            
            break;
        }
    }
}
console.log("ans:", ans);
console.log("count:", count);

let end_t = performance.now();

console.log("split candidates count:");
for(let cand of patterns){
    console.log(cand.length);
}

console.log("sols:");
for(let i = 0; i < sols.length; i += 100){
    console.log(sols.slice(i, i + 100));
}

let ans2 = 0;
for(let x of sols) ans2 += x;

console.log("ans2:", ans2);

console.log("special:", special)

console.log(`${end_t - start_t} milliseconds elapsed`);
















// import "./performance.js";


"use strict";
"esversion: 11"
// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.
// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript
function declareArray(len, init_val) {
    let arr = [];
    for (let i = 0; i < len; i++)
        arr.push(init_val);
    return arr;
}
function incrementBuilder(builder) {
    for (let i = builder.length - 1; i >= 0; i--) {
        if (builder[i] === 0) {
            builder[i]++;
            return;
        }
        builder[i] = 0;
    }
}

function getDigits(num){
    let digits = [];
    while(num > 0){
        digits.push(num % 10);
        num = Math.floor(num / 10);
    }
    let rev = [];
    for(let i = digits.length - 1; i >= 0; i--) rev.push(digits[i]);
    return rev;
}

function check(digits, starts, target) {
    if(starts.length === 2) return false;
    
    let sum = 0;
    for (let i = 1; i < starts.length; i++) { // L is substring len
        let pow10 = 1;
        for(let j = starts[i] - 1; j >= starts[i - 1]; j--){ // this method of extracting digits, then
        // using base 10 mult/add is more than 5x faster than the method of creating all substrings
        // then parseing them to ints using parseInt func, allocating too much memory, too slow
            sum += pow10 * digits[j];
            if(sum > target) return false; // pruning optimization, early return
            pow10 *= 10;
        }
    }
    return sum === target;
}

start_t = performance.now();

pairs = [];
n = 1000000;
//let n = 100;
max_len = (n**2).toString().length;
for (let i = 4; i <= n; i++) { // don't want 1, 4, 9 since can't break them down to at least 2 numbers
    let square = i * i;
    pairs.push([i, square]);
}
patterns = [];

special = [];

for (let len = 0; len <= max_len; len++) {
    if (len < 2) {
        patterns.push([]);
        continue;
    }
    
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    // len >= 2 at this point
    let builder = declareArray(len, 0);
    builder[0] = 1; // 1 means begin a new substring, 0 means continue with current substring
    let ways = 2 ** (len - 1); // Python-esque exponentiation operator 
    let cand = [];
    // x-digit number where x is odd, sqrt root has x / 2 + 1 digits 
    // if x is even, then sqrt has x / 2 digits
    for (let way = 0; way < ways; way++) {
        let starts = [];
        for (let i = 0; i < builder.length; i++) {
            if (builder[i] === 1)
                starts.push(i);
        }
        starts.push(builder.length);
        // find max substring len 
        let max_sub_len = 0;
        for (let i = 1; i < starts.length; i++) { // L is substring len
            let L = starts[i] - starts[i - 1];
            if (L > max_sub_len) max_sub_len = L;
        }
        
        if (max_sub_len >= target_len - 2) {
            
            if(starts[0] === 0 && starts[1] === 1 && starts[2] === 4 && starts[3] === 7){
                console.log("max_sub_len:", max_sub_len, "target_len:", target_len);
            }
            
            // if(max_sub_len === target_len - 2) special.push(starts);
            
            cand.push(starts);
        }
        incrementBuilder(builder);
    }
    patterns.push(cand);
}
// console.log("patterns:", patterns);
console.log("patterns.length", patterns.length);

count = 0;

let sols2 = [];

ans = 0n; // actually don't need bigint, since 
for (let pair of pairs) {
    let num = pair[0];
    let square = pair[1];
    //let s = square.toString();
    let digits = getDigits(square);
    // let len = s.length;
    let len = digits.length;
    let target_len = len / 2;
    if (len % 2 === 1) target_len++;
    
    for (let starts of patterns[len]) {
        let ok = check(digits, starts, num);
        if(ok){
            ans += BigInt(square);
            count++;
            
            let max_sub_len = 0;
            for(let i = 1; i < starts.length; i++){
                let L = starts[i] - starts[i - 1];
                if(L > max_sub_len) max_sub_len = L;
            }
            if(max_sub_len === target_len - 2){
                special.push(num);
            }
            
            sols2.push(square);
            
            if(count < 50){
                console.log("num:", num);
                console.log("square:", square);
                console.log(starts);
                console.log();
            }
            
            break;
        }
    }
}

let hs = new Set();
let hs2 = new Set();
for(let x of sols) hs.add(x);
for(let x of sols2) hs2.add(x);

special = [];
for(let x of hs2){
    if(!hs.has(x)) special.push(x);
}
console.log("special:", special);

console.log("split candidates count:");
for(let cand of patterns){
    console.log(cand.length);
}

*/