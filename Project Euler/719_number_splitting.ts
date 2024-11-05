// Welcome to the TypeScript Playground, this is a website
// which gives you a chance to write, share and learn TypeScript.

// You could think of it in three ways:
//
//  - A location to learn TypeScript where nothing can break
//  - A place to experiment with TypeScript syntax, and share the URLs with others
//  - A sandbox to experiment with different compiler features of TypeScript

function declareArray(len : number, init_val : number) : number[] {
    let arr : number[] = [];
    for(let i : number = 0; i < len; i++) arr.push(init_val);
    return arr;
}

function incrementBuilder(builder : number[]) : void {
    for(let i : number = builder.length - 1; i >= 0; i--){
        if(builder[i] === 0){
            builder[i]++;
            return;
        }
        builder[i] = 0;
    }
}

let pairs : number[][] = [];
let n : number = 1000000;
let max_len : number = (n**2).toString().length;
for(let i : number = 4; i <= n; i++){ // don't want 1, 4, 9 since can't break them down to at least 2 numbers
    let square : number = i * i;
    pairs.push( [i, square] );
}
let patterns : number[][][] = [];
for(let len : number = 0; len <= max_len; len++){
    if(len < 2){
        patterns.push([]);
        continue;
    }
    // len >= 2 at this point
    let builder : number[] = declareArray(len, 0);
    builder[0] = 1; // 1 means begin a new substring, 0 means continue with current substring
    let ways : number = 2 ** (len - 1); // Python-esque exponentiation operator 

    let cand : number[][] = [];

    // x-digit number where x is odd, sqrt root has x / 2 + 1 digits 
    // if x is even, then sqrt has x / 2 digits
    for(let way : number = 0; way < ways; way++){
        let starts : number[] = [];
        for(let i : number = 0; i < builder.length; i++){
            if(builder[i] === 1) starts.push(i);
        }
        // find max substring len 
        let max_sub_len : number = 0;
        for(let i : number = 1; i < starts.length; i++){ // L is substring len
            let L = starts[i] - starts[i - 1];
            if(L > max_sub_len) max_sub_len = L;
        }
        if(len - starts[starts.length - 1] > max_sub_len)
            max_sub_len = len - starts[starts.length - 1];
        
        let target_len : number = len / 2;
        if(len % 2 === 1) target_len++;

        if(max_sub_len >= target_len - 1){
            cand.push(starts);
        }
        incrementBuilder(builder);
    }
    patterns.push(cand);
}

console.log("patterns:", patterns);
console.log("patterns.length", patterns.length);

let ans : bigint = 0n; // actually don't need bigint, since 
for(let pair of pairs){
    let num : number = pair[0];
    let square : number = pair[1];
    let s : string = square.toString();
    let len : number = s.length;
    for(let starts of patterns[len]){
        let sum : number = 0;
        for(let i : number = 1; i < starts.length; i++){ // L is substring len
            let sub : string = s.substring(starts[i - 1], starts[i]);
            let val : number = parseInt(sub);
            sum += val;
        }
        sum += parseInt(s.substring(starts[starts.length - 1], s.length));
        if(sum === num){
            ans += BigInt(square);
            break;
        }
    }
}
console.log("ans:", ans);