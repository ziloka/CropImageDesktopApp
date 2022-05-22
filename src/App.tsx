import React from 'react';
import { BaseSyntheticEvent } from 'react';
import { ButtonGroup, Button, Col } from 'react-bootstrap';
import { listen } from '@tauri-apps/api/event';
import { FileEntry, readDir } from '@tauri-apps/api/fs';
import './App.css';

export class FileViewer extends React.Component<{}, { folderName: string, files: FileEntry[] }> {
  constructor(props: any) {
    super(props);
    this.state = { folderName: '', files: [] };
  }

  async componentDidMount() {
    this.setState({
      folderName: '/home/connor/Downloads/test/teddy bears',
      files: await readDir('/home/connor/Downloads/test/teddy bears')
    });
    listen('folderChanged', async (data: { payload: { folder_name: string } }) => {
      this.setState({
        folderName: data.payload.folder_name,
        files: await readDir(data.payload.folder_name)
      });
    }); 
  }

  /**
   * Function is executed whenever the state is changed
   * @returns 
   */
  render() {
    if (this.state.files.length !== 0) {
      return (
          <ButtonGroup size="lg">
            {
              this.state.files.map((file, i) =>
                <Col>
                  <Button onClick={changeImage} key={i}>{file.name}</Button>
                </Col>
              )
            }
          </ButtonGroup>
      )
    }

    return <div>Loading files...</div>
  }

}

export class ImageViewer extends React.Component<{}, { imageSource: string }> {
  constructor(props: any) {
    super(props);
    this.state = { imageSource: '' };
  }

  render() {
    if (this.state.imageSource.length !== 0) {
      return (
          <img src={this.state.imageSource} alt=""></img>
      )
    }

    return <div>Waiting to load a image...</div>
  }
}

function changeImage(data: BaseSyntheticEvent) {
  console.log('user clicked something', data.target.textContent);
}