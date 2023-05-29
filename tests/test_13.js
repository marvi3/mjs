let s = '', sum = 0, o = {a: 1, b: 2, c: 3};
for (let k in o) {
	print(k);
	s = s + k;
	sum += o[k];
}
let person = ["John", "Doe", "25"]; 

let txt = "";
for (let i in person) {
  txt += person[i] + " ";
}
print(txt);

// Return true if key is present in object, false otherwise
let f = function(obj, key) {
	for (let k in obj) if (k === key) return true;
	return false;
};

print(s === 'cba' && sum === 6 && f(o, 'x') === false && f(o, 'b') === true);
print(s);
print(sum);