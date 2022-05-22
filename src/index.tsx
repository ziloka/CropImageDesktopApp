import ReactDOM from 'react-dom/client';
import { FileViewer, ImageViewer } from './App'
import reportWebVitals from './reportWebVitals';
import './index.css';
import { Container } from 'react-bootstrap';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);

root.render(
  <Container>
    <FileViewer></FileViewer>
    <ImageViewer></ImageViewer>
  </Container>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
