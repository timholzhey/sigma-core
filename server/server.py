from flask import Flask, render_template, request
import subprocess
import os

app = Flask(__name__)

@app.route('/', methods = ['GET'])
def index():
    return render_template('index.html')

@app.route('/solve', methods = ['POST'])
def solve():
    inputfx = request.form['function']
    inputvar = request.form['variable']
    try:
        # if on windows prepend wsl
        cmd = ["sigma", "-c", "derive[" + inputfx + "," + inputvar + "]"]
        if os.name == 'nt':
            cmd = ["wsl"] + cmd
        output = subprocess.check_output(cmd, encoding='utf-8', timeout=1)
        return {'output': output, 'status': 'success'}
    except subprocess.CalledProcessError as e:
        return {'output': 'Error', 'status': 'error'}
    except subprocess.TimeoutExpired as e:
        return {'output': 'Timeout', 'status': 'error'}

if __name__ == '__main__':
    app.run(debug=True)