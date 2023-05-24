pipeline {
    agent any

    stages {
    
        stage('Build') {
            
            steps{
            echo 'Building file...'
            sh 'g++ main.cpp'
            }
        }
        stage('Deploy') {
            when {
              expression {
                currentBuild.result == null || currentBuild.result == 'SUCCESS' 
              }
            }
            steps {
                echo 'Deploying...'
              
            }
        }
    }
}
