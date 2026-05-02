function run() {

    let req = document.getElementById("requests").value
        .split(/[\s,]+/)
        .map(Number)
        .filter(n => !isNaN(n));

    let head = parseInt(document.getElementById("head").value);
    let algo = document.getElementById("algo").value;

    let total = 0;
    let sequence = [head];

    let arr = [...req].sort((a,b)=>a-b);
    let size = 200;

    // ================= FCFS =================
    if(algo === "fcfs") {
        req.forEach(r => {
            if(r === head) return; // 🔥 avoid duplicate
            total += Math.abs(r - head);
            head = r;
            sequence.push(head);
        });
    }

    // ================= SSTF =================
    else if(algo === "sstf") {
        let visited = Array(req.length).fill(false);

        for(let i=0;i<req.length;i++) {
            let min = Infinity, index = -1;

            for(let j=0;j<req.length;j++) {
                if(!visited[j] && req[j] !== head && Math.abs(req[j] - head) < min) {
                    min = Math.abs(req[j] - head);
                    index = j;
                }
            }

            if(index === -1) break;

            visited[index] = true;
            total += min;
            head = req[index];
            sequence.push(head);
        }
    }

    // ================= SCAN =================
    else if(algo === "scan") {

        let left = [];
        let right = [];

        arr.forEach(r => {
            if(r < head) left.push(r);
            else if(r > head) right.push(r); // 🔥 FIX
        });

        // RIGHT SIDE
        for(let i=0;i<right.length;i++) {
            total += Math.abs(right[i] - head);
            head = right[i];
            sequence.push(head);
        }

        // GO TO END
        total += Math.abs(size - head);
        head = size;
        sequence.push(head);

        // LEFT SIDE (REVERSE)
        for(let i=left.length-1;i>=0;i--) {
            total += Math.abs(left[i] - head);
            head = left[i];
            sequence.push(head);
        }
    }

    // ================= C-SCAN =================
    else if(algo === "cscan") {

        let left = [];
        let right = [];

        arr.forEach(r => {
            if(r < head) left.push(r);
            else if(r > head) right.push(r); // 🔥 FIX
        });

        // RIGHT SIDE
        for(let i=0;i<right.length;i++) {
            total += Math.abs(right[i] - head);
            head = right[i];
            sequence.push(head);
        }

        // GO TO END
        total += Math.abs(size - head);
        head = size;
        sequence.push(head);

        // JUMP TO START
        total += size;
        head = 0;
        sequence.push(head);

        // LEFT SIDE
        for(let i=0;i<left.length;i++) {
            total += Math.abs(left[i] - head);
            head = left[i];
            sequence.push(head);
        }
    }

    // ================= LOOK =================
    else if(algo === "look") {

        let left = [];
        let right = [];

        arr.forEach(r => {
            if(r < head) left.push(r);
            else if(r > head) right.push(r); // 🔥 FIX
        });

        // RIGHT SIDE
        for(let i=0;i<right.length;i++) {
            total += Math.abs(right[i] - head);
            head = right[i];
            sequence.push(head);
        }

        // LEFT SIDE (REVERSE)
        for(let i=left.length-1;i>=0;i--) {
            total += Math.abs(left[i] - head);
            head = left[i];
            sequence.push(head);
        }
    }

    // ================= OUTPUT =================
    document.getElementById("algoName").innerText = algo.toUpperCase();
    document.getElementById("sequence").innerText = sequence.join(" → ");
    document.getElementById("seek").innerText = total;

    document.getElementById("resultBox").classList.add("show");
}