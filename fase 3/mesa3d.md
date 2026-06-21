-- html:
<div id="canvas-3d" style="width: 100%; height: 100%; min-height: 300px; display: flex; justify-content: center; align-items: center;"></div>

-- on render:

// Verifica se o Pivot (Caixa) já carregou
if (!htmlNode.threePivot) return;
if (!data || !data.series || data.series.length === 0) return;

let pitch = 0;
let roll = 0;

data.series.forEach((serie) => {
    serie.fields.forEach(f => {
        if (f.type === 'number') {
            const possibleName = `${f.name} ${serie.name} ${f.labels ? JSON.stringify(f.labels) : ''}`.toLowerCase();
            
            let val = 0;
            if (f.values && f.values.length > 0) {
                val = f.values.get ? f.values.get(f.values.length - 1) : f.values[f.values.length - 1];
            }
            
            if (possibleName.includes("pitch")) pitch = val;
            if (possibleName.includes("roll")) roll = val;
        }
    });
});

const pivot = htmlNode.threePivot;

// Converte graus para radianos
const pitchRad = pitch * (Math.PI / 180);
const rollRad = roll * (Math.PI / 180);

// Aplica a inclinação de forma limpa!
// (Se o movimento de ir pra frente estiver tombando a mesa para o lado, basta trocar o 'x' pelo 'z' nessas duas linhas abaixo)
pivot.rotation.x = pitchRad;
pivot.rotation.z = rollRad; 

// Desenha o quadro atualizado
htmlNode.threeRenderer.render(htmlNode.threeScene, htmlNode.threeCamera);

-- on init:

const container = htmlNode.querySelector('#canvas-3d');
if (!container) return;

container.innerHTML = '';
const tempDefine = window.define;
window.define = undefined;

const loadScript = (src) => new Promise((resolve, reject) => {
    const script = document.createElement('script');
    script.src = src;
    script.onload = resolve;
    script.onerror = reject;
    document.head.appendChild(script);
});

async function iniciar3D() {
    try {
        if (typeof window.THREE === 'undefined') {
            await loadScript('https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js');
        }
        if (typeof window.THREE.STLLoader === 'undefined') {
            await loadScript('https://cdn.jsdelivr.net/npm/three@0.128.0/examples/js/loaders/STLLoader.js');
        }

        window.define = tempDefine;

        const width = container.clientWidth || 400;
        const height = container.clientHeight || 400;

        const scene = new window.THREE.Scene();
        const camera = new window.THREE.PerspectiveCamera(50, width / height, 0.1, 100000); 
        
        const renderer = new window.THREE.WebGLRenderer({ alpha: true, antialias: true });
        renderer.setSize(width, height);
        container.appendChild(renderer.domElement);

        const ambientLight = new window.THREE.AmbientLight(0xffffff, 0.8); 
        scene.add(ambientLight);
        const directionalLight = new window.THREE.DirectionalLight(0xffffff, 1);
        directionalLight.position.set(10, 20, 10).normalize();
        scene.add(directionalLight);

        // Salva cena e câmera para o Render
        htmlNode.threeScene = scene;
        htmlNode.threeCamera = camera;
        htmlNode.threeRenderer = renderer;

        const loader = new window.THREE.STLLoader();
        loader.load('/public/assets-3d/mesa.stl', function (geometry) {
            geometry.center(); // Centraliza o labirinto
            
            geometry.computeBoundingBox();
            const size = new window.THREE.Vector3();
            geometry.boundingBox.getSize(size);
            const maxDim = Math.max(size.x, size.y, size.z);
            
            camera.position.set(0, maxDim * 0.5, maxDim * 1.3); 
            camera.lookAt(0, 0, 0);

            const material = new window.THREE.MeshPhongMaterial({ 
                color: 0xcccccc, 
                specular: 0x111111, 
                shininess: 100 
            });
            
            // 1. Cria a mesa
            const mesaMesh = new window.THREE.Mesh(geometry, material);
            // Deita ela de forma fixa
            mesaMesh.rotation.x = -Math.PI / 2; 
            
            // 2. CRIA A CAIXA INVISÍVEL (PIVOT)
            const pivotGroup = new window.THREE.Group();
            pivotGroup.add(mesaMesh); // Coloca a mesa dentro da caixa
            
            scene.add(pivotGroup);
            renderer.render(scene, camera);
            
            // SALVA A CAIXA para ser animada (e não a mesa diretamente)
            htmlNode.threePivot = pivotGroup;
        });

        window.addEventListener('resize', () => {
            if (!container.clientWidth) return;
            renderer.setSize(container.clientWidth, container.clientHeight);
            camera.aspect = container.clientWidth / container.clientHeight;
            camera.updateProjectionMatrix();
        });

    } catch (err) {
        console.error("Erro ao carregar o 3D:", err);
    }
}

iniciar3D();